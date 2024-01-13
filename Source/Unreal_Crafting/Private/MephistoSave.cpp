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

FString UMephistoSave::GetFileDirectory(FString CombinePath)
{
	FString combine = FPaths::Combine(FPaths::ProjectDir() + CombinePath);
	return combine;
}


TArray<uint8>  UMephistoSave::Serializeable(AActor* MyActor)
{
	TArray<uint8> SerializedData;

	if (MyActor)
	{
		FMemoryWriter MemoryWriter(SerializedData);

		FString ActorName = MyActor->GetName();
		FTransform ActorTransform = MyActor->GetTransform();
		TArray<FName> ActorTags = MyActor->Tags;


		MemoryWriter << ActorName;
		MemoryWriter << ActorTransform;
		MemoryWriter << ActorTags;

		MemoryWriter.Close();
	}

	return SerializedData;

}


void UMephistoSave::Deserializeable(const TArray<uint8>& SerializedData)
{

	FMemoryReader MemoryReader(SerializedData, true);

	FString ActorName;
	FTransform ActorTransform;
	TArray<FName> CurrentTags;

	MemoryReader << ActorName;
	MemoryReader << ActorTransform;
	MemoryReader << CurrentTags;

	MemoryReader.Close();


}

std::tuple<int, int> MyFnc()
{

}
