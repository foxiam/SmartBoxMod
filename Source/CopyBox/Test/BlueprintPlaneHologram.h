// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Hologram/FGBuildableHologram.h"
#include "UObject/Object.h"
#include "BlueprintPlaneHologram.generated.h"

/**
 * 
 */
UCLASS()
class COPYBOX_API ABlueprintPlaneHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
