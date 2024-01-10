// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "tuple"
#include "MephistoSave.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_CRAFTING_API UMephistoSave : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	bool WriteFile(FString data);
	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	std::tuple<bool, struct> ReadFile();

};
