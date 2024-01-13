// Fill out your copyright notice in the Description page of Project Settings.


#include "MephistoSave.h"
#include <fstream>
#include <string>
#include <tuple>
#include <Serialization/BufferArchive.h>
#include "Engine/World.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include "Misc/FileHelper.h"
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>

std::string ConvertFStringToStdString(const FString& InFString)
{
	std::string Result(TCHAR_TO_UTF8(*InFString));
	return Result;
}

FString ConvertStdStringToFString(const std::string& InStdString)
{
	FString Result = FString(UTF8_TO_TCHAR(InStdString.c_str()));
	return Result;
}

FString UMephistoSave::ReadFile(const FString& Directory, const FString& FileName, FString& OutData)
{
	FString FullPath = FPaths::Combine(Directory, FileName);
	TArray<uint8> FileData;

	if (!FFileHelper::LoadFileToArray(FileData, *FullPath))
	{
		return FString(TEXT("DATA READS FAIL"));
	}

	OutData = FString(UTF8_TO_TCHAR(FileData.GetData()));

	return OutData;
}

bool UMephistoSave::WriteFile(const FString& Directory, const FString& FileName, const FString& Data)
{
	FString FullPath = FPaths::Combine(Directory, FileName);

	std::string OutData = TCHAR_TO_UTF8(*Data);
	std::string PathFileName = TCHAR_TO_UTF8(*FullPath);
	std::ofstream WriteFile(PathFileName);

	if (WriteFile.is_open()) {
		WriteFile << OutData;
		WriteFile.close();
		return true;
	}
	else {
		return false;
	}
}

FString UMephistoSave::GetFileDirectory()
{
	FString path = FPaths::ProjectDir();
	return path;
}


TArray<uint8>  UMephistoSave::SerializeActor(AActor* MyActor)
{
	TArray<uint8> SerializedData;

	if (MyActor)
	{
		// Bellek üzerinde yazma işlemi için FMemoryWriter kullanılır
		FMemoryWriter MemoryWriter(SerializedData);

		// Actor'ün adını ve transform bilgilerini serialize et
		FString ActorName = MyActor->GetName();
		FTransform ActorTransform = MyActor->GetTransform();
		TArray<FName> ActorTags = MyActor->Tags;


		MemoryWriter << ActorName;
		MemoryWriter << ActorTransform;
		MemoryWriter << ActorTags;

		// Serialize işlemini bitir
		MemoryWriter.Close();
	}

	return SerializedData;

}


void UMephistoSave::DeserializeActor(const TArray<uint8>& SerializedData)
{

	// Bellek üzerinden okuma işlemi için FMemoryReader kullanılır
	FMemoryReader MemoryReader(SerializedData, true);
	// Sınıf tipini, adını ve transform bilgilerini deserialize et
	FString ActorName;
	FTransform ActorTransform;
	TArray<FName> CurrentTags;
	MemoryReader << ActorName;
	MemoryReader << ActorTransform;
	MemoryReader << CurrentTags;
	// Deserialize işlemini bitir
	MemoryReader.Close();
}

