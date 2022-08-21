// Copyright Coffee Stain Studios. All Rights Reserved.


#include "SavedCopy.h"


// Sets default values
ASavedCopy::ASavedCopy() {}

void ASavedCopy::Init(
	const TArray<TSubclassOf<UFGRecipe>>& _Copies,
	const TArray<FTransform>& _RelativeTransforms,
	FString& _CopiesName)
{
	Copies = _Copies;
	RelativeTransforms = _RelativeTransforms;
	CopiesName = _CopiesName;
}
