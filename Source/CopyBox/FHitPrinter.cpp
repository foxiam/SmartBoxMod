// Copyright Coffee Stain Studios. All Rights Reserved.


#include "FHitPrinter.h"

bool AFHitPrinter::IsValidHitResult(const FHitResult& hitResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Hit: %s"), *hitResult.ToString())
	return Super::IsValidHitResult(hitResult);
}
