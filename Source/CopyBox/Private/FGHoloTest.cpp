// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGHoloTest.h"

#include "FGPlayerController.h"
#include "Equipment/FGBuildGunBuild.h"

AFGHoloTest::AFGHoloTest() {}

void AFGHoloTest::BeginPlay()
{
	Super::BeginPlay();
	ConstructionInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
	SectionCopyInteractWidget =CreateWidget<UFGInteractWidget>(
		Cast<AFGPlayerController>(ConstructionInstigator->GetController()),
			SelectionCopyWidget);
	SectionCopyInteractWidget->mInteractObject = this;
	SectionCopyInteractWidget->SetInputMode();
	SectionCopyInteractWidget->AddToViewport(9999);
}

void AFGHoloTest::ChildInit(
	const TArray<TSubclassOf<UFGRecipe>>& ChildRecipe,
	const TArray< FVector > &ChildDeltaPosition )
{
	SectionCopyInteractWidget->mCaptureInput = false;
	SectionCopyInteractWidget->mUseKeyboard = false;
	SectionCopyInteractWidget->mUseMouse=false;
	SectionCopyInteractWidget->SetInputMode();
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

