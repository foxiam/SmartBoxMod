// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <Actor.h>
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableFoundation.h"
#include "Buildables/FGBuildableWire.h"
#include "FGBuildableCB.generated.h"

USTRUCT()
struct COPYBOX_API FSplineData
{
	GENERATED_BODY()
	FTransform Transform;
	TArray<FSplinePointData> SplinePointsData;

	FSplineData() = default;
};

USTRUCT()
struct COPYBOX_API FConnectionWireData
{
	GENERATED_BODY()
	FVector ConnectionLocation0;
	FVector ConnectionLocation1;

	FConnectionWireData() = default;
};

USTRUCT(BlueprintType)
struct COPYBOX_API FDataOfCopiedBuildable
{
	GENERATED_BODY()
	TArray<TPair<TSubclassOf<UFGRecipe>, FTransform>> OtherBuildable;
	TArray<TPair<TSubclassOf<UFGRecipe>, FSplineData>> SplineBuildable;
	TArray<TPair<TSubclassOf<UFGRecipe>, FConnectionWireData>> Wire;
	FDataOfCopiedBuildable() = default;
};

/**
 * 
 */
UCLASS( Abstract )
class COPYBOX_API AFGBuildableCB : public AFGBuildable
{
	GENERATED_BODY()
	
public:

	AFGBuildableCB();

	virtual void BeginPlay() override;
	
	void AddBuildable(AFGBuildable *Buildable);
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void SaveCopy(FString CopiesName);

	UPROPERTY()
	AFGBuildableFoundation *MainFoundation;

protected:

	void AddConveyor(const AFGBuildableConveyorBelt *Conveyor);

	void AddWire(const AFGBuildableWire *Wire);
	
	void AddOtherBuildable(const AFGBuildable *Buildable);

	FDataOfCopiedBuildable DataOfCopied;
};
