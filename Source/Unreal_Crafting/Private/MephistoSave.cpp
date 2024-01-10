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

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FullPath))
	{
		return FString(TEXT("DATA READS FAIL"));
	}

	OutData = FString(UTF8_TO_TCHAR(FileData.GetData()));

	return OutData;
}

FString UMephistoSave::GetFileDirectory()
{
	FString path = FPaths::ProjectDir();
	return path;
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
