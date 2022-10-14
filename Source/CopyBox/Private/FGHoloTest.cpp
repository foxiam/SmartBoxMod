// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"
#include "FGPlayerController.h"
#include "FGSplineComponent.h"
#include "FGSplineMeshGenerationLibrary.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Hologram/FGWireHologram.h"

AFGHoloTest::AFGHoloTest() {}

void AFGHoloTest::BeginPlay()
{
	Super::BeginPlay();
	ConstructionInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
	if(ConstructionInstigator)
		ConstructionInit(ConstructionInstigator);
}

void AFGHoloTest::ChildInit(const FDataOfCopiedBuildable DataOfCopied, float _mHeight)
{
	SetIsChanged(true);
	mHeight = _mHeight;
	for(const auto BuildableData : DataOfCopied.OtherBuildable)
		OtherBuildableHolograms.Emplace(SpawnChildHolo(BuildableData.Key, BuildableData.Value));
	
	for(const auto SplineData : DataOfCopied.SplineBuildable)
	{
		auto ConveyorHolo = Cast<AFGConveyorBeltHologram>(SpawnChildHolo(SplineData.Key, SplineData.Value.Transform));
		ConveyorHolo->mSplineComponent->SetSplineData(SplineData.Value.SplinePointsData, ESplineCoordinateSpace::Local);
		
		UFGSplineMeshGenerationLibrary::BuildSplineMeshes(
			ConveyorHolo->mSplineComponent,
			ConveyorHolo->mMaxSplineLength,
			ConveyorHolo->mMesh,
			ConveyorHolo->mMeshLength,
			ConveyorHolo->mSplineMeshes,
			[ConveyorHolo]( USplineComponent* spline)
			{
				USplineMeshComponent* newComponent =
					NewObject< USplineMeshComponent >(
						spline->GetOwner(), USplineMeshComponent::StaticClass(), NAME_None,
						RF_NoFlags, ConveyorHolo->mSplineMeshes[0]);
				newComponent->SetupAttachment( ConveyorHolo->GetRootComponent() );
				newComponent->Mobility = EComponentMobility::Movable;
				return newComponent;
			}
		);
		
		ConveyorsHolograms.Emplace(ConveyorHolo);
	}

	for(auto WireData : DataOfCopied.Wire)
	{
		FWireData WireHologramData;
		WireHologramData.Hologram =
			Cast<AFGWireHologram>(SpawnChildHolo(WireData.Key, FTransform(WireData.Value.ConnectionLocation0)));
		WireHologramData.Connection = WireData.Value;
		WireHolograms.Emplace();
	}
}

AFGHologram* AFGHoloTest::SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform, bool Rotate)
{
	SpawnChildHologramFromRecipe(this, Recipe,this, Transform.GetLocation());
	if(Rotate) mChildren.Last()->SetActorRotation(Transform.Rotator());
	mChildren.Last()->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	return mChildren.Last();
}

void AFGHoloTest::ConstructOtherBuildable() const
{
	TArray<AActor*> Temp;
	for(const auto buildable : OtherBuildableHolograms)
		buildable->Construct(Temp, GetLocalPendingConstructionID());
}

void AFGHoloTest::ConstructConveyorBelt() const
{
	TArray<AActor*> Temp;

	auto FindConnect = [this](const FVector ConnectionPos)
	{
		return UFGFactoryConnectionComponent::FindOverlappingConnections(
				GetWorld(),
				ConnectionPos,
				200,
				EFactoryConnectionConnector::FCC_CONVEYOR,
				EFactoryConnectionDirection::FCD_ANY);
	};
	
	for(const auto ConveyorHologram : ConveyorsHolograms)
	{
		const int PointsNum = ConveyorHologram->mSplineComponent->GetNumberOfSplinePoints();
		const FVector ConnectionLocation0 =
			ConveyorHologram->mSplineComponent->GetSplinePointData(0, ESplineCoordinateSpace::World).Location;
		const FVector ConnectionLocation1 =
			ConveyorHologram->mSplineComponent->GetSplinePointData(PointsNum - 1, ESplineCoordinateSpace::World).Location;
		
		UFGFactoryConnectionComponent *OtherConnection0 = FindConnect(ConnectionLocation0);
		UFGFactoryConnectionComponent *OtherConnection1 = FindConnect(ConnectionLocation1);
		
		const AFGBuildableConveyorBelt *Conveyor =
			Cast<AFGBuildableConveyorBelt>(ConveyorHologram->Construct(Temp, GetLocalPendingConstructionID()));
		
		if(OtherConnection0 && Conveyor->GetConnection0()->CanConnectTo(OtherConnection0))
			Conveyor->GetConnection0()->SetConnection(OtherConnection0);
		
		if(OtherConnection1 && Conveyor->GetConnection1()->CanConnectTo(OtherConnection1))
			Conveyor->GetConnection1()->SetConnection(OtherConnection1);
	}
}

void AFGHoloTest::ConstructWire() const
{
	auto GenerateFakeHit = [this](FVector Pos)
	{
		return FHitResult(
			nullptr,
			nullptr,
			Pos.RotateAngleAxis(GetActorRotation().Yaw, FVector(0, 0, 1)) + GetActorLocation(),
			FVector::ZeroVector
			);
	};

	TArray<AActor*> Temp;
	
	for(const auto WireData : WireHolograms)
	{
		WireData.Hologram->SetHologramLocationAndRotation(GenerateFakeHit(WireData.Connection.ConnectionLocation0));
		WireData.Hologram->DoMultiStepPlacement(true);
		WireData.Hologram->SetHologramLocationAndRotation(GenerateFakeHit(WireData.Connection.ConnectionLocation1));
		WireData.Hologram->DoMultiStepPlacement(true);
		WireData.Hologram->Construct(Temp, GetLocalPendingConstructionID());
	}
}

bool AFGHoloTest::DoMultiStepPlacement(bool isInputFromARelease)
{
	ConstructOtherBuildable();
	ConstructConveyorBelt();
	ConstructWire();
	return false;
}
