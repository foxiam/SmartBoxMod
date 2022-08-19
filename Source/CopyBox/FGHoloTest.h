// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGHoloTest.generated.h"

/**
 * 
 */
UCLASS()
class COPYBOX_API AFGHoloTest : public AFGBuildableHologram
{
	GENERATED_BODY()
	AFGHoloTest();
public:
	virtual void BeginPlay() override;

	void ChildInit(const TArray< TSubclassOf< UFGRecipe > > &ChildRecipe, const TArray< FVector > &ChildDeltaPosition);
	
private:
	UPROPERTY()
	TArray< AFGHologram* > ChildHolograms;
	
	UPROPERTY()
	AFGCharacterPlayer *ConstructionInstigator;
};
