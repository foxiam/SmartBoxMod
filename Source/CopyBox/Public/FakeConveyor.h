// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "FakeConveyor.generated.h"

UCLASS()
class COPYBOX_API AFakeConveyor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFakeConveyor();

	void GenerateFakeConveyor(
		UStaticMesh* ConveyorMesh,
		TArray<FSplinePointData> SplinePointData
		);
	
	UPROPERTY()
	USplineComponent *SplineComponent;
	UPROPERTY()
	TArray< USplineMeshComponent* > SplineMeshComponents;

protected:
	virtual void BeginPlay() override;
};
