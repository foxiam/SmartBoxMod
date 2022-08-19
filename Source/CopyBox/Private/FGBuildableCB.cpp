// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGBuildableCB.h"

#include "FGBuildableCopy.h"
#include "Hologram/FGHologram.h"


AFGBuildableCB::AFGBuildableCB() : Super()
{
	this->mSkipBuildEffect = true;
}

FString AFGBuildableCB::GetHologramName(AFGBuildable *build)
{
	return build->mHologramClass->GetName();
}


