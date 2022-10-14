// Copyright Coffee Stain Studios. All Rights Reserved.


#include "BuildableCopyBox.h"

#include "CopyBack.h"

ABuildableCopyBox::ABuildableCopyBox()
{
}
void ABuildableCopyBox::BeginPlay()
{
	TArray<FHitResult> HitResults;
	const FVector TraceStart = GetActorLocation() + GetActorForwardVector() * 10.0f + GetActorRightVector() * 10.0f;
	const FVector TraceEnd = TraceStart - GetActorUpVector() * 50.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams);

	UE_LOG(LogTemp, Warning, TEXT("NumHit: %d"), HitResults.Num())
	
	for(auto resultHit : HitResults)
	{
		if(auto foundation =  Cast<AFGBuildableFoundation>(resultHit.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("foundation found"))
			MainFoundation = foundation;
			break;
		}
	}
	Super::BeginPlay();
}

void ABuildableCopyBox::AddBuildable(AFGBuildable* Buildable)
{
	
}

void ABuildableCopyBox::SaveCopy(FString CopiesName)
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, AFGBuildable::StaticClass());

	ACopyBack *newSavedCopy = GetWorld()->SpawnActor<ACopyBack>(ACopyBack::StaticClass());
	TArray<FTransform> Transforms;
	for(auto t : overlappingActors)
	{
		FActorSpawnParameters a;
		a.Template = t;
		FVector loc = t->GetTransform().GetLocation();
		loc = FVector(800, 0, 0);
		if(AActor *tmp = Cast<AFGBuildable>(GetWorld()->SpawnActor(t->GetClass(), &loc, &FRotator::ZeroRotator, a)))
		{
			tmp->SetActorHiddenInGame(false);
		}
		Transforms.Emplace(t->GetTransform().GetRelativeTransform(MainFoundation->GetTransform()));
	}
	newSavedCopy->Init(overlappingActors, Transforms);
	UE_LOG(LogTemp, Warning, TEXT("Try create"))
}

