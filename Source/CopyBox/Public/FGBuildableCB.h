// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <Actor.h>
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableFoundation.h"
#include "FGBuildableCB.generated.h"

USTRUCT()
struct COPYBOX_API FConnectionData
{
	GENERATED_BODY()

	FTransform Transform;
	TArray< FSplinePointData > SplinePointData;
	UPROPERTY()
	UStaticMesh* StaticMesh;
	FVector startPos;
	FVector startNormal;
	FVector endPos;
	FVector endNormal;

	FConnectionData() = default;
};

USTRUCT(BlueprintType)
struct COPYBOX_API FDataOfCopiedObj
{
	GENERATED_BODY()

	float mainHeight;
	
	TArray < TPair < TSubclassOf < UFGRecipe >, FTransform > > Buildables;
	TArray < TPair < TSubclassOf < UFGRecipe >,  FConnectionData > > Conveyors;

	FDataOfCopiedObj() = default;
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

protected:

	void AddConveyor(AFGBuildableConveyorBelt *Conveyor);
	
	void AddOtherBuildable(const AFGBuildable *Buildable);

	FDataOfCopiedObj DataOfCopied;
	
	UPROPERTY()
	AFGBuildableFoundation *MainFoundation;
};
