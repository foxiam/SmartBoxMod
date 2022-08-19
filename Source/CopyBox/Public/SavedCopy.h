// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "GameFramework/Actor.h"
#include "SavedCopy.generated.h"

UCLASS()
class COPYBOX_API ASavedCopy : public AActor
{
	GENERATED_BODY()

public:
	ASavedCopy();

	void Init(const TArray<TSubclassOf< UFGRecipe >>& _Copies, const TArray<FVector>& _DeltaPosition, FString& _CopiesName);
	
	TArray<TSubclassOf< UFGRecipe >> Copies;
	TArray<FVector> DeltaPosition;
	FString CopiesName;
};
