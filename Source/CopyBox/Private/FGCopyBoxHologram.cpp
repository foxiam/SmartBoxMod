// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGCopyBoxHologram.h"
#include "FGPlayerController.h"
#include "SavedCopy.h"
#include "Buildables/FGBuildableFoundation.h"

AFGCopyBoxHologram::AFGCopyBoxHologram()
{
	mBuildStep = ECBHBuildStep::PlacementAndRotation;
}

void AFGCopyBoxHologram::BeginPlay()
{
	ConstructionInstigator = Cast<AFGCharacterPlayer>(
			this->GetConstructionInstigator());
	EnableInput(Cast<AFGPlayerController>(ConstructionInstigator->GetController()));
	Super::BeginPlay();
}

void AFGCopyBoxHologram::ScaleZ(float Value)
{
	FVector Scale = GetRootComponent()->GetRelativeScale3D();
	Scale.Z += Value;
	if(0 < Scale.Z && Scale.Z < 100) GetRootComponent()->SetWorldScale3D(Scale);
}

bool AFGCopyBoxHologram::DoMultiStepPlacement(bool isInputFromARelease)
{
	const bool SuperBool = Super::DoMultiStepPlacement(isInputFromARelease);
	switch (mBuildStep)
	{
		case ECBHBuildStep::PlacementAndRotation:
			mBuildStep = ECBHBuildStep::ScalingXY;
			deltaRotate = GetRootComponent()->GetComponentRotation().Yaw -
				static_cast<int>(GetRootComponent()->GetComponentRotation().Yaw / 90) * 90;
			break;
		case ECBHBuildStep::ScalingXY: mBuildStep = ECBHBuildStep::SczlingZ; break;
		default: mBuildStep = ECBHBuildStep::Build; break;
	}
	return  SuperBool && mBuildStep == ECBHBuildStep::Build;
}

bool AFGCopyBoxHologram::IsValidHitResult(const FHitResult& hitResult) const
{
	const bool checkValidClass = Cast<AFGBuildableFoundation>(hitResult.GetActor()) != nullptr;
	if(mBuildStep == ECBHBuildStep::PlacementAndRotation) return checkValidClass && Super::IsValidHitResult(hitResult);
	return true;
}

void AFGCopyBoxHologram::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	if(mBuildStep == ECBHBuildStep::PlacementAndRotation) Super::SetHologramLocationAndRotation(hitResult);
	else if(mBuildStep == ECBHBuildStep::ScalingXY)
	{
		const FVector deltaHit =
			(hitResult.Location - GetActorLocation()).RotateAngleAxis(-deltaRotate, FVector(0, 0, 1));
		int X = FMath::Max(abs(static_cast<int>(deltaHit.X / 100)) * 5, 5);
		int Y = FMath::Max(abs(static_cast<int>(deltaHit.Y / 100)) * 5, 5);
		if(deltaHit.X >=0 && deltaHit.Y >= 0) SetActorRotation(FRotator(0, 0 + deltaRotate, 0));
		else if(deltaHit.X >=0 && deltaHit.Y < 0)
		{
			SetActorRotation(FRotator(0, -90 + deltaRotate, 0));
			Swap(X, Y);
		}
		else if(deltaHit.X < 0 && deltaHit.Y < 0) SetActorRotation(FRotator(0, 180 + deltaRotate, 0));
		else if(deltaHit.X < 0 && deltaHit.Y >= 0)
		{
			SetActorRotation(FRotator(0, 90 + deltaRotate, 0));
			Swap(X, Y);
		};
		if(X < 1000 && Y < 1000) GetRootComponent()->SetWorldScale3D(FVector(X, Y, 1));
	}
}





