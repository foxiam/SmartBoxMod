// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FakeConnection.generated.h"

UCLASS()
class COPYBOX_API AFakeConnection : public AFGBuildable
{
	GENERATED_BODY()

public:

	AFakeConnection();

	UPROPERTY( VisibleAnywhere, Category = "Connection" )
	class UFGFactoryConnectionComponent* mSnapOnly0;
	
protected:

	virtual void BeginPlay() override;
};
