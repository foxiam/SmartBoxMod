// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableFoundation.h"
#include "BuildableCopyBox.generated.h"

UCLASS()
class COPYBOX_API ABuildableCopyBox : public AFGBuildable
{
	GENERATED_BODY()

public:
	
	ABuildableCopyBox();

	virtual void BeginPlay() override;
	
	void AddBuildable(AFGBuildable *Buildable);
	
	UFUNCTION(BlueprintCallable, Category="UFUNCTION")
	void SaveCopy(FString CopiesName);

	UPROPERTY()
	AFGBuildableFoundation *MainFoundation;
	
};
