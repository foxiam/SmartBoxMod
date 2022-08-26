// Copyright Coffee Stain Studios. All Rights Reserved.


#include "SavedCopy.h"


// Sets default values
ASavedCopy::ASavedCopy() {}

void ASavedCopy::Init(FDataOfCopiedObj _DataOfCopiedObj, FString& _CopiesName)
{
	DataOfCopiedObj = _DataOfCopiedObj;
	CopiesName = _CopiesName;
}
