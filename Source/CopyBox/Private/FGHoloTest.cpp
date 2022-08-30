// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"
#include "FGPlayerController.h"
#include "FGSplineComponent.h"
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
		OtherBuildableHolograms.Emplace(SpawnChildHolo(child.Key, child.Value));
		if(AFGBuildableHologram *BuildableHologram = Cast<AFGBuildableHologram>(OtherBuildableHolograms.Last()))
		{
			BuildableHologram->mNeedsValidFloor = false;
		}
	}
	for(auto ConveyorData : DataOfCopiedObj.Conveyors)
	{
		FConnectionData CData = ConveyorData.Value;
		
		FakeConnections.Emplace(GetWorld()->SpawnActor<AFakeConnection>(FakeConnection ,CData.startPos, CData.startNormal.Rotation()));
		
		FakeConnections.Emplace(GetWorld()->SpawnActor<AFakeConnection>(FakeConnection, CData.endPos, CData.endNormal.Rotation()));
		
		AFGConveyorBeltHologram *Conveyor =
			Cast<AFGConveyorBeltHologram>(SpawnChildHolo(ConveyorData.Key));
		ConveyorConnectionHelper(Conveyor, ConveyorData.Value.startPos - FVector(0, 0, 100), ConveyorData.Value.startNormal);
		ConveyorConnectionHelper(Conveyor, ConveyorData.Value.endPos - FVector(0, 0, 100), ConveyorData.Value.endNormal);
		ConveyorsHolograms.Add(Conveyor);
	}

	for(const auto childHologram : mChildren)
		childHologram->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

AFGHologram* AFGHoloTest::SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform, bool Rotate)
{
	SpawnChildHologramFromRecipe(this, Recipe,this, Transform.GetLocation());
	if(Rotate) mChildren.Last()->SetActorRotation(Transform.Rotator());
	return mChildren.Last();
}

void AFGHoloTest::ConstructAll(TArray<AFGHologram*> childHolograms) const
{
	TArray<AActor*> Temp;
	while(childHolograms.Num() != 0)
	{
		AFGHologram *child = childHolograms.Pop();
		child->Construct(Temp, GetLocalPendingConstructionID());
	}
}

void AFGHoloTest::ConveyorConnectionHelper(AFGConveyorBeltHologram *Conveyor, FVector Pos, FVector Normal) const
{
	
	const FHitResult FakeHit = FHitResult(
			nullptr,
			nullptr,
			Pos - Normal * 30,
			Normal
		);
	
	Conveyor->SetHologramLocationAndRotation(FakeHit);
	Conveyor->DoMultiStepPlacement(true);
}

void AFGHoloTest::DestroyedFakeConnections()
{
	while(FakeConnections.Num() > 0)
	{
		AFakeConnection *Fake = FakeConnections.Pop();
		Fake->Destroy();
	}
}

void AFGHoloTest::Destroyed()
{
	Super::Destroyed();
	DestroyedFakeConnections();
}

bool AFGHoloTest::DoMultiStepPlacement(bool isInputFromARelease)
{
	ConstructAll(OtherBuildableHolograms);
	DestroyedFakeConnections();
	TArray<AActor*> Temp;
	for(const auto ChildrenConveyorHolograms : ConveyorsHolograms)
	{
		UFGFactoryConnectionComponent *OtherConnection0 =
			UFGFactoryConnectionComponent::FindOverlappingConnections(
				GetWorld(),
				ChildrenConveyorHolograms->GetCachedFactoryConnectionComponents()[0]->GetConnectorLocation(),
				150,
				EFactoryConnectionConnector::FCC_CONVEYOR,
				EFactoryConnectionDirection::FCD_ANY);
		
		UFGFactoryConnectionComponent *OtherConnection1 =
			UFGFactoryConnectionComponent::FindOverlappingConnections(
				GetWorld(),
				ChildrenConveyorHolograms->GetCachedFactoryConnectionComponents()[1]->GetConnectorLocation(),
				150,
				EFactoryConnectionConnector::FCC_CONVEYOR,
				EFactoryConnectionDirection::FCD_ANY);

		const AFGBuildableConveyorBelt *Conveyor =
			Cast<AFGBuildableConveyorBelt>(ChildrenConveyorHolograms->Construct(Temp, GetLocalPendingConstructionID()));
		
		if(OtherConnection0 && Conveyor->GetConnection0()->CanConnectTo(OtherConnection0))
		{
			Conveyor->GetConnection0()->ClearConnection();
			Conveyor->GetConnection0()->SetConnection(OtherConnection0);
		}
		
		if(OtherConnection1 && Conveyor->GetConnection1()->CanConnectTo(OtherConnection1))
		{
			Conveyor->GetConnection1()->ClearConnection();
			Conveyor->GetConnection1()->SetConnection(OtherConnection1);
		}
	}
	return true;
}
