// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGHoloTest.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COPYBOX_API AFGHoloTest : public AFGBuildableHologram
{
	GENERATED_BODY()
	AFGHoloTest();
public:
	
	virtual void BeginPlay() override;

	virtual void CheckValidFloor() override;

	UFUNCTION(BlueprintCallable)
	void ChildInit(const TArray<TSubclassOf<UFGRecipe>>& ChildRecipe,
	               const TArray<FTransform>& ChildRelativeTransforms);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ConstructionInit(AFGCharacterPlayer *ConstructionInitInstigator);

	UPROPERTY()
	AFGCharacterPlayer *ConstructionInstigator;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SelectionCopyWidget;

	UPROPERTY()
	UFGInteractWidget *SectionCopyInteractWidget;
	
	UPROPERTY()
	TArray< AFGHologram* > ChildHolograms;
};
