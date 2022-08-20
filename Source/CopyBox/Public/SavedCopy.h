﻿// Copyright Coffee Stain Studios. All Rights Reserved.

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

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf< UFGRecipe >> Copies;
	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> DeltaPosition;
	UPROPERTY(BlueprintReadOnly)
	FString CopiesName;
};
