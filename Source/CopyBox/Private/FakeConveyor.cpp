// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FakeConveyor.h"

#include "FGSplineMeshGenerationLibrary.h"


// Sets default values
AFakeConveyor::AFakeConveyor()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("mSplineComponent"));
}

void AFakeConveyor::GenerateFakeConveyor(
	UStaticMesh* ConveyorMesh,
	TArray<FSplinePointData> SplinePointData
	)
{
	SplineComponent->SetSplineData(SplinePointData, ESplineCoordinateSpace::Local);
	UFGSplineMeshGenerationLibrary::BuildSplineMeshes(
		SplineComponent,
		SplineComponent->GetSplineLength(),
		ConveyorMesh,
		200.0,
		SplineMeshComponents,
		[]( USplineComponent* spline)
		{
			USplineMeshComponent* newComponent =
				NewObject< USplineMeshComponent >(spline->GetOwner(), USplineMeshComponent::StaticClass());
			newComponent->SetupAttachment( spline );
			newComponent->Mobility = EComponentMobility::Movable;
			newComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			return newComponent;
		}
	);
}

void AFakeConveyor::BeginPlay()
{
	Super::BeginPlay();
}

