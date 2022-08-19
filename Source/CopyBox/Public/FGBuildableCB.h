// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <Actor.h>
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableCB.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class COPYBOX_API AFGBuildableCB : public AFGBuildable
{
	GENERATED_BODY()
public:

	AFGBuildableCB();

	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void AddBuildable(AActor* OverlappedActor);
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void SaveCopy(FString CopiesName) const;

protected:
	
	TArray<TSubclassOf< UFGRecipe >> Copies;
	TArray<FVector> DeltaPosition;
};
