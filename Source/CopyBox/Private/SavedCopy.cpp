// Copyright Coffee Stain Studios. All Rights Reserved.


#include "SavedCopy.h"


// Sets default values
ASavedCopy::ASavedCopy() {}

void ASavedCopy::Init(const TArray<TSubclassOf<UFGRecipe>>& _Copies, const TArray<FVector>& _DeltaPosition, FString& _CopiesName)
{
	Copies = _Copies;
	DeltaPosition = _DeltaPosition;
	CopiesName = _CopiesName;
}
