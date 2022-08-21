// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"

#include "FGPlayerController.h"
#include "Equipment/FGBuildGunBuild.h"

AFGHoloTest::AFGHoloTest() {}

void AFGHoloTest::BeginPlay()
{
	Super::BeginPlay();
	ConstructionInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
	if(ConstructionInstigator)
		ConstructionInit(ConstructionInstigator);
}

void AFGHoloTest::ChildInit(
	const TArray<TSubclassOf<UFGRecipe>>& ChildRecipe,
	const TArray< FTransform > &ChildRelativeTransforms )
{
	for(int i = 0; i < ChildRecipe.Num(); i++)
	{
		SpawnChildHologramFromRecipe(
			this,
			ChildRecipe[i],
			this,
			ChildRelativeTransforms[i].GetLocation()
		);
		mChildren[i]->SetActorRotation(ChildRelativeTransforms[i].GetRotation());
		mChildren[i]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

