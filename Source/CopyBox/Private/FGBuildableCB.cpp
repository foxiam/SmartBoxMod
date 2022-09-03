// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGBuildableCB.h"

#include "FGBuildableCopy.h"
#include "SavedCopy.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableFoundation.h"
#include "Hologram/FGWireHologram.h"
#include "Hologram/HologramHelpers.h"


AFGBuildableCB::AFGBuildableCB() : Super()
{
}

void AFGBuildableCB::BeginPlay()
{
	TArray<FHitResult> HitResults;
	const FVector TraceStart = GetActorLocation() + GetActorForwardVector() * 10.0f + GetActorRightVector() * 10.0f;
	const FVector TraceEnd = TraceStart - GetActorUpVector() * 50.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams);

	UE_LOG(LogTemp, Warning, TEXT("NumHit: %d"), HitResults.Num())
	
	for(auto resultHit : HitResults)
	{
		if(auto foundation =  Cast<AFGBuildableFoundation>(resultHit.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("foundation found"))
			MainFoundation = foundation;
			break;
		}
	}
	
	Super::BeginPlay();
}

void AFGBuildableCB::AddBuildable(AFGBuildable* Buildable)
{
	if(const auto *Conveyor = Cast<AFGBuildableConveyorBelt>(Buildable))
	{
		AddConveyor(Conveyor);
	}
	else if(const auto *Wire = Cast<AFGWireHologram>(Buildable))
	{
		
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
	newSavedCopy->Init(DataOfCopied, CopiesName, MainFoundation->mHeight);
}

void AFGBuildableCB::AddConveyor(const AFGBuildableConveyorBelt* Conveyor)
{
	FSplineData SplineData;
	SplineData.Transform = Conveyor->GetTransform().GetRelativeTransform(MainFoundation->GetTransform());
	SplineData.SplinePointsData = Conveyor->GetSplineData();
	DataOfCopied.SplineBuildable.Emplace(Conveyor->GetBuiltWithRecipe(), SplineData);
}

void AFGBuildableCB::AddWire(const AFGBuildableWire* Wire)
{
	FConnectionWireData WireData;
	WireData.ConnectionLocation0 =FTransform(
		Wire->GetLocation(0)).GetRelativeTransform(MainFoundation->GetTransform()).GetLocation();
	WireData.ConnectionLocation1 = FTransform(
		Wire->GetLocation(1)).GetRelativeTransform(MainFoundation->GetTransform()).GetLocation();
	DataOfCopied.Wire.Emplace(Wire->GetBuiltWithRecipe(), WireData);
}

void AFGBuildableCB::AddOtherBuildable(const AFGBuildable* Buildable)
{
	if(Buildable)
	{
		DataOfCopied.OtherBuildable.Emplace(
			Buildable->GetBuiltWithRecipe(),
			Buildable->GetTransform().GetRelativeTransform(MainFoundation->GetTransform())
			);
	}
}
