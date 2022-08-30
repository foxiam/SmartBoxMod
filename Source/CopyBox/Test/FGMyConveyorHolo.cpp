// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGMyConveyorHolo.h"

#include "FakeConnection.h"
#include "WwiseItemType.h"

void AFGMyConveyorHolo::BeginPlay()
{
	Super::BeginPlay();
	auto *FakeConnection = GetWorld()->SpawnActor<AFakeConnection>();
	mSnappedConnectionComponents[0] = GetCachedFactoryConnectionComponents()[0];
	mMeshLength = 500;
	ResetConstructDisqualifiers();
}

void AFGMyConveyorHolo::SetHologramLocationAndRotation(const FHitResult& hitResult)
{}

bool AFGMyConveyorHolo::DoMultiStepPlacement(bool isInputFromARelease)
{
	return true;
}

bool AFGMyConveyorHolo::IsConnectionSnapped(bool lastConnection)
{
	return true;
}
