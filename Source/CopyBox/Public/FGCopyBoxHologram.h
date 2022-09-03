// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGCopyBoxHologram.generated.h"

UENUM()
enum class ECBHBuildStep : uint8
{
	PlacementAndRotation,
	ScalingXY,
	SczlingZ,
	Build
};

UCLASS()
class COPYBOX_API AFGCopyBoxHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	
	AFGCopyBoxHologram();
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void ScaleZ(float Value);
	
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;

	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	
protected:
	
	ECBHBuildStep mBuildStep;

	float deltaRotate;

	UPROPERTY()
	const AFGCharacterPlayer* ConstructionInstigator;
};
