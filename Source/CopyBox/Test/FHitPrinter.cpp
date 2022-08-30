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
	UE_LOG(LogTemp, Error, TEXT("Location: %s"), *hit.Location.ToString())
	UE_LOG(LogTemp, Error, TEXT("Normal: %s"), *hit.Normal.ToString())
	UFGFactoryConnectionComponent *con = UFGFactoryConnectionComponent::FindOverlappingConnections(
		GetWorld(),
		hit.Location,
		200,
		EFactoryConnectionConnector::FCC_CONVEYOR,
		EFactoryConnectionDirection::FCD_ANY);
	UE_LOG(LogTemp, Warning, TEXT("Con find: %s"), con ? TEXT("true") : TEXT("false"));
	return false;
}
