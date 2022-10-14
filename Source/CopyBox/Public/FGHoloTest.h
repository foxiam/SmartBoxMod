// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableCB.h"
#include "Hologram/FGFoundationHologram.h"
#include "FGHoloTest.generated.h"

USTRUCT()
struct COPYBOX_API FWireData
{
	GENERATED_BODY()
	
	UPROPERTY()
	AFGWireHologram* Hologram;
	FConnectionWireData Connection;
	
	FWireData() = default;
};

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
	void ChildInit(const FDataOfCopiedBuildable DataOfCopied, float _mHeight);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ConstructionInit(AFGCharacterPlayer *ConstructionInitInstigator);

	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;

	AFGHologram* SpawnChildHolo(TSubclassOf<UFGRecipe> Recipe, FTransform Transform, bool Rotate = true);

	void ConstructOtherBuildable() const;

	void ConstructConveyorBelt() const;

	void ConstructWire() const;

	UPROPERTY()
	AFGCharacterPlayer *ConstructionInstigator;
	
protected:
	UPROPERTY()
	TArray<AFGConveyorBeltHologram*> ConveyorsHolograms;

	UPROPERTY()
	TArray<FWireData> WireHolograms;

	UPROPERTY()
	TArray<AFGHologram*> OtherBuildableHolograms;
};
