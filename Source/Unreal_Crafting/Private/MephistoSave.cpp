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

TArray<uint8> UMephistoSave::Serializeable(const FString& Data)
{
	TArray<uint8> SerializedData;

	TArray<uint8> DataArray((uint8*)Data.GetCharArray().GetData(), Data.Len() * sizeof(TCHAR));

	SerializedData += DataArray;
	return SerializedData;
}

FString UMephistoSave::Deserializeable(const TArray<uint8>& SerializedData)
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


TArray<uint8>  UMephistoSave::SerializeActor(AActor* MyActor)
{

	if (!MyActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Null (boş) bir AActor nesnesi gönderildi."));
		return TArray<uint8>();
	}

	FBufferArchive Ar;

	//// Burada MyActor'ü yazmak için Ar kullanılır
	Ar << MyActor;

	// Son olarak, Ar'ın bellek içeriğini kullanarak TArray<uint8> oluşturulur
	TArray<uint8> OutData;
	OutData.Append(Ar.GetData(), Ar.Num());
	//FString name = MyActor->GetName();
	//UE_LOG(LogTemp, Error, TEXT("%s"), *name);


	return OutData;
}

AActor* UMephistoSave::DeserializeActor(UWorld* World, const TArray<uint8>& SerializedData)
{
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("UWorld geçerli değil."));
		return nullptr;
	}

	// Bellek içeriğini okumak için FMemoryReader kullanılır
	FMemoryReader Ar(SerializedData, true);

	AActor* NewActor = World->SpawnActor<AActor>();

	if (NewActor)
	{
		// Burada NewActor'ü okumak için Ar kullanılır
		Ar << NewActor;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Yeni bir AActor örneği oluşturulamadı."));
	}

	return NewActor;
}


bool UMephistoSave::SWriteFile(const FString& FilePath, const TArray<uint8>& Data)
{
	return FFileHelper::SaveArrayToFile(Data, *FilePath);
}

bool UMephistoSave::SReadFile(const FString& FilePath, TArray<uint8>& OutData)
{
	return FFileHelper::LoadFileToArray(OutData, *FilePath);
}
