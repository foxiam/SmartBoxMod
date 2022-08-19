// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <Actor.h>

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "UObject/Object.h"
#include "FGBuildableCopy.generated.h"

/**
 * 
 */
UCLASS()
class COPYBOX_API AFGBuildableCopy : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableCopy();
	
	void Init(TArray<TSubclassOf<AActor>> mCopyActors);

	virtual void BeginPlay() override;
};
