// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FakeConnection.h"

#include "FGFactoryConnectionComponent.h"
#include "Equipment/FGAmmoTypeInstantHit.h"


// Sets default values
AFakeConnection::AFakeConnection()
{
	mSnapOnly0 = CreateDefaultSubobject<UFGFactoryConnectionComponent>(TEXT("SnapOnly0"));
	mSnapOnly0->SetupAttachment(RootComponent);
}

void AFakeConnection::BeginPlay()
{
	Super::BeginPlay();
	this->SetHiddenIngameAndHideInstancedMeshes(false);
}
