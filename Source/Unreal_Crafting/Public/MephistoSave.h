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

	UFUNCTION(Category = "Mephisto Save")
	static TArray<uint8> Serializeable(const FString& Data);

	UFUNCTION(Category = "Mephisto Save")
	static FString Deserializeable(const TArray<uint8>& SerializedData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mephisto Save")
	static FString GetFileDirectory();

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static TArray<uint8> SerializeActor(AActor* MyActor);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static AActor* DeserializeActor(UWorld* World, const TArray<uint8>& SerializedData);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static bool SWriteFile(const FString& FilePath, const TArray<uint8>& Data);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static bool SReadFile(const FString& FilePath, TArray<uint8>& OutData);


};
