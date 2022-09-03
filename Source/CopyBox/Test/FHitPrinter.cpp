// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FHitPrinter.h"

#include "FGCharacterPlayer.h"
#include "FGFactoryConnectionComponent.h"
#include "Equipment/FGBuildGun.h"

void AFHitPrinter::BeginPlay()
{
	Super::BeginPlay();
	ConstructorInstigator = Cast<AFGCharacterPlayer>(GetConstructionInstigator());
}

bool AFHitPrinter::IsValidHitResult(const FHitResult& hitResult) const
{
	return true;
}

bool AFHitPrinter::DoMultiStepPlacement(bool isInputFromARelease)
{
	FHitResult hit = ConstructorInstigator->GetBuildGun()->GetHitResult();
	if(hit.Actor.Get())
		UE_LOG(LogTemp, Error, TEXT("Name: %s"), *hit.Actor.Get()->GetName())
	UE_LOG(LogTemp, Error, TEXT("Location: %s"), *hit.Location.ToString())
	UE_LOG(LogTemp, Error, TEXT("Normal: %s"), *hit.Normal.ToString())
	if(step == 0)
	{
		copy.Emplace(hit.Actor.Get());
		t = copy[0]->GetTransform();
		step++;
	}
	else if(step < 3)
	{
		copy.Emplace(hit.Actor.Get());
		step++;
	}
	else if(step == 3)
	{
		for(auto u : copy)
		{
			FActorSpawnParameters a;
			a.Template = u;
			const FTransform v = u->GetTransform().GetRelativeTransform(t);
			AActor* c = GetWorld()->SpawnActor(u->StaticClass(), &v, a);
		}
	}
	return false;
}
