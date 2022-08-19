// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <Actor.h>

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableFactory.h"
#include "Resources/FGBuildingDescriptor.h"
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
	FString GetHologramName(AFGBuildable *build);
};
