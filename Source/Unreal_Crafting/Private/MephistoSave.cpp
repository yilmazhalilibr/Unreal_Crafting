// Fill out your copyright notice in the Description page of Project Settings.


#include "MephistoSave.h"
#include <fstream>
#include <string>
#include <tuple>

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

	TArray<uint8> SerializedData;
	if (!FFileHelper::LoadFileToArray(SerializedData, *FullPath))
	{
		FString out = "Fail read";
		return out;
	}

	OutData = Deserialize(SerializedData);

	return OutData;
}

bool UMephistoSave::WriteFile(const FString& Directory, const FString& FileName, const FString& Data)
{
	TArray<uint8> SerializedData = Serialize(Data);

	FString FullPath = FPaths::Combine(Directory, FileName);


	return FFileHelper::SaveArrayToFile(SerializedData, *FullPath);
}

TArray<uint8> UMephistoSave::Serialize(const FString& Data)
{
	TArray<uint8> SerializedData;

	TArray<uint8> DataArray((uint8*)Data.GetCharArray().GetData(), Data.Len() * sizeof(TCHAR));

	SerializedData += DataArray;
	return SerializedData;
}

FString UMephistoSave::Deserialize(const TArray<uint8>& SerializedData)
{
	FString DeserializedData;

	DeserializedData = FString((TCHAR*)SerializedData.GetData(), SerializedData.Num() / sizeof(TCHAR));

	return DeserializedData;
}

FString UMephistoSave::GetFileDirectory()
{
	FString path = FPaths::ProjectDir();
	return path;
}
