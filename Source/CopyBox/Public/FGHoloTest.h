// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <utility>

#include "CoreMinimal.h"
#include "FakeConnection.h"
#include "FGBuildableCB.h"
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

	AFGHologram* SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform = FTransform(), bool Rotate = true);

	void ConstructAll(TArray<AFGHologram*> childHolograms) const;

	void ConveyorConnectionHelper(AFGConveyorBeltHologram *Conveyor, FVector Pos, FVector Normal) const;

	UPROPERTY()
	AFGCharacterPlayer *ConstructionInstigator;

	FDataOfCopiedObj DataOfCopiedObj;
	
protected:
	
	void DestroyedFakeConnections();

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFakeConnection> FakeConnection;
	
	UPROPERTY()
	TArray<AFakeConnection*> FakeConnections;

	UPROPERTY()
	TArray<AFGConveyorBeltHologram*> ConveyorsHolograms;

	UPROPERTY()
	TArray<AFGHologram*> OtherBuildableHolograms;
};
