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

bool UMephistoSave::WriteFile(FString Path, FString data)
{
	std::string path = ConvertFStringToStdString(Path);
	std::string outData = ConvertFStringToStdString(data);

	std::ofstream writeFile(path);

	if (writeFile.is_open()) {
		writeFile << outData;
		writeFile.close();
		return true;
	}
	else 
	{
		return false;
	}

}

FString UMephistoSave::ReadFile(FString Path)
{
	std::string path = ConvertFStringToStdString(Path);
	std::ifstream readFile(path);
	if (readFile.is_open())
	{
		readFile.seekg(0, std::ios::beg);

		std::string data;
		while (readFile >> data)
		{
			FString newData = ConvertStdStringToFString(data);
			return newData;
		}

		readFile.close();
	}
	else {
		return FString();

	}

	return FString();
}




