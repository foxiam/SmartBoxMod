// Copyright Coffee Stain Studios. All Rights Reserved.


#include "CopyBack.h"


// Sets default values
ACopyBack::ACopyBack()
{}

void ACopyBack::Init(TArray<AActor*> copy, TArray<FTransform> transform)
{
	UE_LOG(LogTemp, Warning, TEXT("Copy succesful create"))
	CopyBuildables = copy;
	TransformCopy = transform;
}



