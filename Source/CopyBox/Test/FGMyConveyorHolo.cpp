// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGMyConveyorHolo.h"

#include "FakeConnection.h"
#include "FGConstructDisqualifier.h"
#include "Patching/NativeHookManager.h"
#include "WwiseItemType.h"

void AFGMyConveyorHolo::BeginPlay()
{
	Super::BeginPlay();
}

void AFGMyConveyorHolo::SetHologramLocationAndRotation(const FHitResult& hitResult)
{
	//Super::SetHologramLocationAndRotation(hitResult);
}

bool AFGMyConveyorHolo::DoMultiStepPlacement(bool isInputFromARelease)
{
	return true;
	//return Super::DoMultiStepPlacement(isInputFromARelease);
}