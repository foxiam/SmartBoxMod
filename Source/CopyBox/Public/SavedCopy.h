// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableCB.h"
#include "GameFramework/Actor.h"
#include "SavedCopy.generated.h"

UCLASS()
class COPYBOX_API ASavedCopy : public AActor
{
	GENERATED_BODY()

public:
	ASavedCopy();

	void Init(const FDataOfCopiedObj _DataOfCopiedObj, FString& _CopiesName);

	UPROPERTY(BlueprintReadOnly)
	FDataOfCopiedObj DataOfCopiedObj;
	UPROPERTY(BlueprintReadOnly)
	FString CopiesName;
};
