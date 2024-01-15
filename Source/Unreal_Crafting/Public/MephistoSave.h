// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MephistoSave.generated.h"

/**
 *
 */
//
//USTRUCT(BlueprintType)
//struct FMyStruct
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FString Name;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 Age;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<TArray<uint8>> ArrayList;
//};


UCLASS()
class UNREAL_CRAFTING_API UMephistoSave : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static bool WriteFile(const FString& Directory, const FString& FileName, const FString& Data);
	
	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static FString BytesArrayConvertToString(TArray<uint8> data);

	static FString StringFromBytes(const TArray<uint8>& Bytes);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static FString ReadFile(const FString& Directory, const FString& FileName, FString& OutData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mephisto Save")
	static FString GetFileDirectory(FString CombinePath);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static TArray<uint8> Serializeable(AActor* MyActor);
	
	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static TArray<uint8> Serializeables(TArray<AActor*> MyActors);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static AActor* Deserializeable(TArray<UClass*> classType, UWorld* World, const TArray<uint8>& SerializedData);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static bool WriteDataToFile(const FString& Directory, const FString& FileName, const TArray<FString>& Data);

	UFUNCTION(BlueprintCallable, Category = "Mephisto Save")
	static TArray<FString> ReadDataFromFile(const FString& Directory, const FString& FileName);

		///////
	/*UFUNCTION(BlueprintCallable, Category = "MyStructHelper")
	static bool SaveStructToFile(const FString& FilePath, const FMyStruct& Data);

	UFUNCTION(BlueprintCallable, Category = "MyStructHelper")
	static bool LoadStructFromFile(const FString& FilePath, FMyStruct& OutData);*/

};
