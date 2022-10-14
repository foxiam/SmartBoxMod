// Copyright Coffee Stain Studios. All Rights Reserved.


#include "BlueprintPlaneHologram.h"

#include "CopyBack.h"

void ABlueprintPlaneHologram::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACopyBack::StaticClass(), FoundActors);
	if(FoundActors.Num()) {
		UE_LOG(LogTemp, Warning, TEXT("Copy init"))
		ACopyBack *copys = Cast<ACopyBack>(FoundActors[0]);
		for(int i = 0; i < copys->CopyBuildables.Num(); i++)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Template = copys->CopyBuildables[i];
			AActor *copy = GetWorld()->SpawnActor(copys->CopyBuildables[i]->GetClass() ,&copys->TransformCopy[i], SpawnParameters);
			copy->GetRootComponent()->Mobility = EComponentMobility::Movable;
			copy->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			copy->SetActorEnableCollision(false);
			copy->SetActorHiddenInGame(false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail init"))
	}
}
