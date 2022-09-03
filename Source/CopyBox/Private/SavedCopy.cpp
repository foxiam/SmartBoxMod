// Copyright Coffee Stain Studios. All Rights Reserved.


#include "SavedCopy.h"

// Sets default values
ASavedCopy::ASavedCopy() {}

void ASavedCopy::Init(const FDataOfCopiedBuildable _DataOfCopied, FString& _CopiesName, float _mHeight)
{
	DataOfCopied = _DataOfCopied;
	CopiesName = _CopiesName;
	mHeight = _mHeight;
}
