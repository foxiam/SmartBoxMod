// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGMyConveyorHolo.h"

#include "WwiseItemType.h"

void AFGMyConveyorHolo::BeginPlay()
{
	Super::BeginPlay();
	switch(mBuildStep)
	{
		case ESplineHologramBuildStep::SHBS_FindStart:
			UE_LOG(LogTemp, Warning, TEXT("Build Step: FindStart")) break;
		case ESplineHologramBuildStep::SHBS_PlacePoleOrSnapEnding:
			UE_LOG(LogTemp, Warning, TEXT("Build Step: PlacePoleOrSnapEnding")) break;
		case ESplineHologramBuildStep::SHBS_AdjustPole:
			UE_LOG(LogTemp, Warning, TEXT("Build Step: AdjustPole")); break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Build Step: NULL")); break;
	}
	AFGHologram *a = SpawnChildHologramFromRecipe(this, ConveyorAttach, this, GetActorLocation() + FVector(0, 0, 150));
}

bool AFGMyConveyorHolo::IsValidHitResult(const FHitResult& hitResult) const
{
	return Super::IsValidHitResult(hitResult);
}

void AFGMyConveyorHolo::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	FHitResult FakeHit(nullptr, nullptr, hitResult.Location, FVector::ZeroVector);
	Super::SetHologramLocationAndRotation(hitResult);
}

bool AFGMyConveyorHolo::DoMultiStepPlacement(bool isInputFromARelease)
{
	switch(mBuildStep)
	{
		case ESplineHologramBuildStep::SHBS_FindStart:
			UE_LOG(LogTemp, Warning, TEXT("Connection0: %s"), *mCachedFactoryConnectionComponents[0]->GetComponentLocation().ToString()) break;
		case ESplineHologramBuildStep::SHBS_PlacePoleOrSnapEnding:
			UE_LOG(LogTemp, Warning, TEXT("Connection1: %s"), *mCachedFactoryConnectionComponents[1]->GetComponentLocation().ToString()) break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Build Step: NULL")); break;
	}
	return Super::DoMultiStepPlacement(isInputFromARelease);
}
