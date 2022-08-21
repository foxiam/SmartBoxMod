// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGBuildableCB.h"

#include "FGBuildableCopy.h"
#include "SavedCopy.h"
#include "GenericPlatform/GenericPlatformMath.h"


AFGBuildableCB::AFGBuildableCB() : Super() {}

void AFGBuildableCB::AddBuildable(AActor* OverlappedActor)
{
	if(const AFGBuildable *Buildable = Cast<AFGBuildable>(OverlappedActor))
	{
		Copies.Add(Buildable->GetBuiltWithRecipe());
		FTransform BRTransform = Buildable->GetTransform().GetRelativeTransform(GetTransform());
		FVector BuildableLocation = BRTransform.GetLocation();
		FVector CS = GetActorScale3D();
		BuildableLocation.X *= CS.X;
		BuildableLocation.Y *= CS.Y;
		BuildableLocation.Z *= CS.Z;
		BRTransform = FTransform(BRTransform.GetRotation(), BuildableLocation);
		RelativeTransforms.Add(BRTransform);
	}
}

void AFGBuildableCB::SaveCopy(FString CopiesName) const
{
	ASavedCopy *Copy = GetWorld()->SpawnActor<ASavedCopy>(ASavedCopy::StaticClass(), FTransform());
	Copy->Init(Copies, RelativeTransforms, CopiesName);
}




