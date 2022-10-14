// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "GameFramework/Actor.h"
#include "CopyBack.generated.h"

UCLASS()
class COPYBOX_API ACopyBack : public AActor
{
	GENERATED_BODY()

public:
	ACopyBack();

	void Init(TArray<AActor*> copy, TArray<FTransform> transform);

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> CopyBuildables;

	TArray<FTransform> TransformCopy;
};
