// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MephistoSave.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_CRAFTING_API UMephistoSave : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static bool WriteFile(FString Path, FString Data);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static FString ReadFile(FString Path);

};
