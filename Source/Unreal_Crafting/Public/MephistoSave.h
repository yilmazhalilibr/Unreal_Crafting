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
	static bool WriteFile(const FString& Directory, const FString& FileName, const FString& Data);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static FString ReadFile(const FString& Directory, const FString& FileName, FString& OutData);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mephisto Save")
	static FString GetFileDirectory();


};
