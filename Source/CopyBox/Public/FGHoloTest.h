// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FakeConveyor.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGBuildableCB.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Hologram/FGFoundationHologram.h"
#include "FGHoloTest.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COPYBOX_API AFGHoloTest : public AFGFoundationHologram
{
	GENERATED_BODY()
	AFGHoloTest();
public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ChildInit(FDataOfCopiedObj _DataOfCopiedObj);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ConstructionInit(AFGCharacterPlayer *ConstructionInitInstigator);

	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	AFGHologram* SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform, bool Rotate = true);

	void ConstructChild();

	void ConveyorConnectionHelper(AFGConveyorBeltHologram *Conveyor, FVector Pos, FVector Normal);

	UPROPERTY()
	AFGCharacterPlayer *ConstructionInstigator;

	FDataOfCopiedObj DataOfCopiedObj;
	
protected:
	UPROPERTY()
	TArray<AFakeConveyor*> FakeConveyors;

	void DestroyedFakeConveyors();

	virtual void Destroyed() override;
};
