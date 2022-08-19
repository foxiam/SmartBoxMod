// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FGBuildableCopy.h"
AFGBuildableCopy::AFGBuildableCopy() {}

void AFGBuildableCopy::Init(TArray<TSubclassOf<AActor>> mCopyActors)
{
	for(auto copyActor : mCopyActors)
	{
		UChildActorComponent *build = NewObject<UChildActorComponent>(this, FName(copyActor->GetName()));
		build->SetupAttachment(RootComponent);
		build->SetChildActorClass(copyActor);
		build->RegisterComponent();
	}
}

void AFGBuildableCopy::BeginPlay()
{
	Super::BeginPlay();
}
