// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGCopyBoxHologram.generated.h"

UENUM()
enum class ECBHBuildStep : uint8
{
	CBHBS_PlacementAndRotation,
	CBHBS_Hold,
	CBHBS_Build
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
	void ScaleX(float Value);
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void ScaleY(float Value);
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void ScaleZ(float Value);
	
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;

	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	
protected:
	
	bool HoldMode = false;
	ECBHBuildStep mBuildStep;

	UPROPERTY()
	const AFGCharacterPlayer* ConstructionInstigator;
};
