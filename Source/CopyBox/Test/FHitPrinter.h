﻿// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "UObject/Object.h"
#include "FHitPrinter.generated.h"

/**
 * 
 */
UCLASS()
class COPYBOX_API AFHitPrinter : public AFGBuildableHologram
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFGBuildable> build;

	UPROPERTY()
	AFGCharacterPlayer* ConstructorInstigator;

	int step = 0;

	UPROPERTY();
	TArray<AActor*> copy;

	FTransform t;
};
