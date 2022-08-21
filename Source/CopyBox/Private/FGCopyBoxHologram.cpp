// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGCopyBoxHologram.h"
#include "FGPlayerController.h"
#include "SavedCopy.h"
#include "Buildables/FGBuildableFoundation.h"

AFGCopyBoxHologram::AFGCopyBoxHologram()
{
	mBuildStep = ECBHBuildStep::CBHBS_PlacementAndRotation;
}

void AFGCopyBoxHologram::BeginPlay()
{
	ConstructionInstigator = Cast<AFGCharacterPlayer>(
			this->GetConstructionInstigator());
	Super::BeginPlay();
	EnableInput(Cast<AFGPlayerController>(ConstructionInstigator->GetController()));
}

void AFGCopyBoxHologram::ScaleX(float Value)
{
	FVector Scale = GetRootComponent()->GetRelativeScale3D();
	Scale.X += Value;
	if(0 < Scale.X && Scale.X < 100) GetRootComponent()->SetWorldScale3D(Scale);
}

void AFGCopyBoxHologram::ScaleY(float Value)
{
	FVector Scale = GetRootComponent()->GetRelativeScale3D();
	Scale.Y += Value;
	if(0 < Scale.Y && Scale.Y < 100) GetRootComponent()->SetWorldScale3D(Scale);
}

void AFGCopyBoxHologram::ScaleZ(float Value)
{
	FVector Scale = GetRootComponent()->GetRelativeScale3D();
	Scale.Z += Value;
	if(0 < Scale.Z && Scale.Z < 100) GetRootComponent()->SetWorldScale3D(Scale);
}

bool AFGCopyBoxHologram::DoMultiStepPlacement(bool isInputFromARelease)
{
	for(auto comp : GetComponents())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *comp->GetName());
	}
	const bool SuperBool = Super::DoMultiStepPlacement(isInputFromARelease);
	mBuildStep = mBuildStep == ECBHBuildStep::CBHBS_PlacementAndRotation ?
		ECBHBuildStep::CBHBS_Hold : ECBHBuildStep::CBHBS_Build;
	HoldMode = !HoldMode;
	return  SuperBool && mBuildStep == ECBHBuildStep::CBHBS_Build;
}

bool AFGCopyBoxHologram::IsValidHitResult(const FHitResult& hitResult) const
{
	const bool checkValidClass = Cast<AFGBuildableFoundation>(hitResult.GetActor());
	if(!HoldMode) return checkValidClass && Super::IsValidHitResult(hitResult);
	return true;
}

void AFGCopyBoxHologram::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	if(!HoldMode) Super::SetHologramLocationAndRotation(hitResult);
}






