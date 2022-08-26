// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGBuildableCB.h"

#include "AkAcousticPortal.h"
#include "FGBuildableCopy.h"
#include "FGFactoryConnectionComponent.h"
#include "SavedCopy.h"
#include "../../../../../../Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/include/filesystem"
#include "Buildables/FGBuildableConveyorBase.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableFoundation.h"
#include "Hologram/HologramHelpers.h"
#include "Kismet/KismetMathLibrary.h"


AFGBuildableCB::AFGBuildableCB() : Super() {}

void AFGBuildableCB::BeginPlay()
{
	Super::BeginPlay();
	FHitResult resultHit;
	const FVector TraceStart = GetActorLocation() + GetActorForwardVector() * 10.0f;
	const FVector TraceEnd = GetActorLocation() - GetActorUpVector() * 100.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(resultHit, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams);

	if(resultHit.bBlockingHit && IsValid(resultHit.GetActor()))
	{
		MainFoundation = Cast<AFGBuildableFoundation>(resultHit.GetActor());
		if(MainFoundation) DataOfCopied.mainHeight = MainFoundation->mHeight;
	}
}

void AFGBuildableCB::AddBuildable(AFGBuildable* Buildable)
{
	if(AFGBuildableConveyorBelt *ConveyorBase = Cast<AFGBuildableConveyorBelt>(Buildable))
	{
		AddConveyor(ConveyorBase);
	}
	else
	{
		AddOtherBuildable(Buildable);
	}
}

void AFGBuildableCB::SaveCopy(FString CopiesName)
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, AFGBuildable::StaticClass());
	
	for(const auto Buildable : overlappingActors)
	{
		AddBuildable(Cast<AFGBuildable>(Buildable));
	}

	ASavedCopy *newSavedCopy = GetWorld()->SpawnActor<ASavedCopy>(ASavedCopy::StaticClass());
	newSavedCopy->Init(DataOfCopied, CopiesName);
}

void AFGBuildableCB::AddConveyor(AFGBuildableConveyorBelt* Conveyor)
{
	auto GetRelativeLocation = [this](const UFGFactoryConnectionComponent* Connection)
	{
		return FTransform(Connection->GetConnectorLocation()).
			GetRelativeTransform(MainFoundation->GetTransform()).GetLocation();
	};
	const float Yaw = MainFoundation->GetActorRotation().Yaw;
	FConnectionData ConnectionData;
	UE_LOG(LogTemp, Warning, TEXT("Rot: %f"), Yaw)
	ConnectionData.Transform = Conveyor->GetTransform().GetRelativeTransform(MainFoundation->GetTransform());
	ConnectionData.SplinePointData = Conveyor->GetSplineComponent()->GetSplineData(ESplineCoordinateSpace::Local);
	ConnectionData.StaticMesh = Conveyor->GetSplineMesh();
	ConnectionData.startPos = GetRelativeLocation(Conveyor->GetConnection0());
	ConnectionData.startNormal = Conveyor->GetConnection0()->GetConnectorNormal().RotateAngleAxis(-Yaw, FVector(0, 0, 1));
	ConnectionData.endPos = GetRelativeLocation(Conveyor->GetConnection1());
	ConnectionData.endNormal = Conveyor->GetConnection1()->GetConnectorNormal().RotateAngleAxis(-Yaw, FVector(0, 0, 1));
	DataOfCopied.Conveyors.Emplace(Conveyor->GetBuiltWithRecipe(), ConnectionData);
}

void AFGBuildableCB::AddOtherBuildable(const AFGBuildable* Buildable)
{
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Buildable->GetName())
	UE_LOG(LogTemp, Warning, TEXT("	Location target: %s"),
		*Buildable->GetTransform().GetRelativeTransform(MainFoundation->GetTransform()).GetLocation().ToString())
	TPair<TSubclassOf<UFGRecipe>, FTransform> BuildalesData(
			Buildable->GetBuiltWithRecipe(),
			Buildable->GetTransform().GetRelativeTransform(MainFoundation->GetTransform()));
	DataOfCopied.Buildables.Emplace(BuildalesData);
}