// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include <basetyps.h>

#include "CoreMinimal.h"
#include "Hologram/FGConveyorBeltHologram.h"
#include "Patching/NativeHookManager.h"
#include "FGMyConveyorHolo.generated.h"
/**
 * 
 */
UCLASS()
class COPYBOX_API AFGMyConveyorHolo : public AFGConveyorBeltHologram
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;

	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
};