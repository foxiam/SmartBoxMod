// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"

#include <xutility>

#include "FakeConveyor.h"
#include "FGPlayerController.h"
#include "FGSplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Equipment/FGBuildGunBuild.h"
#include "Hologram/FGConveyorBeltHologram.h"

AFGHoloTest::AFGHoloTest() {}

void AFGHoloTest::BeginPlay()
{
	Super::BeginPlay();
	ConstructionInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
	if(ConstructionInstigator)
		ConstructionInit(ConstructionInstigator);
}

void AFGHoloTest::ChildInit(FDataOfCopiedObj _DataOfCopiedObj)
{
	DataOfCopiedObj = _DataOfCopiedObj;
	mHeight = DataOfCopiedObj.mainHeight;
	for(auto child : DataOfCopiedObj.Buildables)
	{
		SpawnChildHolo(child.Key, child.Value);
	}
	for(auto conveyor : DataOfCopiedObj.Conveyors)
	{
		FConnectionData CData= conveyor.Value;
		AFakeConveyor *FakeConveyor = GetWorld()->SpawnActor<AFakeConveyor>
			(CData.Transform.GetLocation(), CData.Transform.Rotator());
		FakeConveyor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		FakeConveyor->GenerateFakeConveyor(CData.StaticMesh, CData.SplinePointData);
		FakeConveyors.Emplace(FakeConveyor);
	}
}

AFGHologram* AFGHoloTest::SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform, bool Rotate)
{
	SpawnChildHologramFromRecipe(
		this,
			Recipe,
			this,
			Transform.GetLocation());
	if(Rotate) mChildren.Last()->SetActorRotation(Transform.Rotator());
	mChildren.Last()->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	return mChildren.Last();
}

void AFGHoloTest::ConstructChild()
{
	TArray<AActor*> Temp;
	while(mChildren.Num() != 0)
	{
		AFGHologram *child = mChildren.Pop();
		child->Construct(Temp, GetLocalPendingConstructionID());
		child->Destroy();
	}
}

void AFGHoloTest::ConveyorConnectionHelper(AFGConveyorBeltHologram *Conveyor, FVector Pos, FVector Normal)
{
	auto RotateAngleZ = [this](FVector Vec)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rot: %f"), GetActorRotation().Yaw)
		return Vec.RotateAngleAxis(GetActorRotation().Yaw,
			FVector(0, 0, 1));
	};
	UE_LOG(LogTemp, Warning, TEXT("Pos: %s"), *(RotateAngleZ(Pos) + GetActorLocation()).ToString())
	UE_LOG(LogTemp, Warning, TEXT("Normal: %s"), *RotateAngleZ(Normal).ToString())
	
	const FHitResult FakeHit = FHitResult(
			nullptr,
			nullptr,
			RotateAngleZ(Pos) + GetActorLocation() - (RotateAngleZ(Normal) * 10),
			RotateAngleZ(Normal)
		);
	
	Conveyor->SetHologramLocationAndRotation(FakeHit);
	Conveyor->DoMultiStepPlacement(true);
}

void AFGHoloTest::DestroyedFakeConveyors()
{
	while(FakeConveyors.Num() > 0)
	{
		FakeConveyors.Pop()->Destroy();
	}
}

void AFGHoloTest::Destroyed()
{
	Super::Destroyed();
	DestroyedFakeConveyors();
}

bool AFGHoloTest::DoMultiStepPlacement(bool isInputFromARelease)
{
	ConstructChild();
	DestroyedFakeConveyors();
	for(auto ConveyorData : DataOfCopiedObj.Conveyors)
	{
		AFGConveyorBeltHologram *Conveyor = Cast<AFGConveyorBeltHologram>(
			SpawnChildHolo(ConveyorData.Key, ConveyorData.Value.Transform)
		);
		ConveyorConnectionHelper(Conveyor, ConveyorData.Value.startPos - FVector(0, 0, 100), ConveyorData.Value.startNormal);
		ConveyorConnectionHelper(Conveyor, ConveyorData.Value.endPos - FVector(0, 0, 100), ConveyorData.Value.endNormal);
	}
	ConstructChild();
	return true;
}
