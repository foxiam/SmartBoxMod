// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGBuildableCB.h"

#include "FGBuildableCopy.h"
#include "SavedCopy.h"
#include "Hologram/FGHologram.h"


AFGBuildableCB::AFGBuildableCB() : Super()
{
	this->mSkipBuildEffect = true;
}

void AFGBuildableCB::AddBuildable(AActor* OverlappedActor)
{
	if(const AFGBuildable *Buildable = Cast<AFGBuildable>(OverlappedActor))
	{
		Copies.Add(Buildable->GetBuiltWithRecipe());
		DeltaPosition.Add(FVector::ZeroVector);
		if(Buildable->GetBuiltWithRecipe()->GetDefaultObject())
		{
			UE_LOG(LogTemp, Error, TEXT("Recipe name: %s"), *Buildable->GetBuiltWithRecipe()->GetDefaultObject()->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Recipe name: NULL"));
		}
	}
}

void AFGBuildableCB::SaveCopy(FString CopiesName) const
{
	ASavedCopy *Copy = GetWorld()->SpawnActor<ASavedCopy>(ASavedCopy::StaticClass(), FTransform());
	Copy->Init(Copies, DeltaPosition, CopiesName);
}


