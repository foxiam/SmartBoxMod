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

	UFUNCTION(BlueprintCallable)
	void ChildInit(const TArray< TSubclassOf< UFGRecipe > > &ChildRecipe, const TArray< FVector > &ChildDeltaPosition);

	UPROPERTY(BlueprintReadOnly)
	AFGCharacterPlayer *ConstructionInstigator;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SelectionCopyWidget;

	UPROPERTY()
	UFGInteractWidget *SectionCopyInteractWidget;
	
	UPROPERTY()
	TArray< AFGHologram* > ChildHolograms;
};
