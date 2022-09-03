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

	void Init(const FDataOfCopiedBuildable _DataOfCopied, FString& _CopiesName, float _mHeight);

	
	UPROPERTY(BlueprintReadOnly)
	FDataOfCopiedBuildable DataOfCopied;
	
	UPROPERTY(BlueprintReadOnly)
	FString CopiesName;
	
	UPROPERTY(BlueprintReadOnly)
	float mHeight;
};
