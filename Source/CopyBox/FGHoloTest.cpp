// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"

#include "FGBuildableCopy.h"
#include "FGPlayerController.h"
#include "Engine/InheritableComponentHandler.h"
#include "Equipment/FGBuildGunBuild.h"
#include "GenericPlatform/GenericPlatformMath.h"

AFGHoloTest::AFGHoloTest()
{
	ConstructionInstigator = nullptr;
}

void AFGHoloTest::BeginPlay()
{
	Super::BeginPlay();
	ConstructionInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
}

void AFGHoloTest::ChildInit(
	const TArray<TSubclassOf<UFGRecipe>>& ChildRecipe,
	const TArray< FVector > &ChildDeltaPosition )
{
	for(int i = 0; i < ChildRecipe.Num(); i++)
	{
		ChildHolograms.Add(SpawnChildHologramFromRecipe(
			this,
			ChildRecipe[i],
			this,
			ChildDeltaPosition[i])
		);
		ChildHolograms[i]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

