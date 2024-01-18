// Fill out your copyright notice in the Description page of Project Settings.


#include "MephistoSave.h"
#include <fstream>
#include <string>
#include <tuple>
#include <Serialization/BufferArchive.h>
#include "Engine/World.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>
#include <algorithm>

////////////////////
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

FString UMephistoSave::BytesArrayConvertToString(TArray<uint8> data)
{
	FString OutString;
	if (data.Num() == 0)
	{
		OutString.Empty();
	}

	OutString = FString(data.Num(), reinterpret_cast<const TCHAR*>(data.GetData()));

	return OutString;
}

FString UMephistoSave::StringFromBytes(const TArray<uint8>& Bytes)
{
	return FString(reinterpret_cast<const TCHAR*>(Bytes.GetData()), Bytes.Num());
}

////////////////////

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

		FString ActorName = MyActor->Tags[1].ToString();
		FTransform ActorTransform = MyActor->GetTransform();
		TArray<FName> ActorTags = MyActor->Tags;


		MemoryWriter << ActorName;
		MemoryWriter << ActorTransform;
		MemoryWriter << ActorTags;

		//UE_LOG(LogTemp, Warning, TEXT("Name %s"), *ActorName);

		MemoryWriter.Close();
	}

	return SerializedData;

}


AActor* UMephistoSave::Deserializeable(TArray<UClass*> classType, UWorld* World, const TArray<uint8>& SerializedData)
{
	AActor* SpawnedActor = nullptr;


	FMemoryReader MemoryReader(SerializedData, true);

	FString ActorName;
	FTransform ActorTransform;
	TArray<FName> CurrentTags;

	MemoryReader << ActorName;
	MemoryReader << ActorTransform;
	MemoryReader << CurrentTags;

	MemoryReader.Close();



	for (UClass* classData : classType)
	{

		if (classData->GetName().Contains(ActorName))
		{

			UE_LOG(LogTemp, Warning, TEXT("Success"));

			SpawnedActor = World->GetWorld()->SpawnActor<AActor>(classData);

			SpawnedActor->SetActorLabel(ActorName);
			SpawnedActor->SetActorTransform(ActorTransform);
			SpawnedActor->Tags = CurrentTags;

			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("Failed To ClassData"));
	}



	//if (SpawnedActor)
	//{
	//	SpawnedActor->SetActorLabel(ActorName);
	//	SpawnedActor->SetActorTransform(ActorTransform);
	//	SpawnedActor->Tags = CurrentTags;
	//}

	return SpawnedActor;
}

void UMephistoSave::DeserializeableList(TArray<UClass*> classType, UWorld* World, const TArray<FS_BytesArrayList>& SerializedData)
{
	AActor* SpawnedActor = nullptr;


	for (auto firstList : SerializedData)
	{

		FMemoryReader MemoryReader(firstList.DataArray, true);

		FString ActorName;
		FTransform ActorTransform;
		TArray<FName> CurrentTags;

		MemoryReader << ActorName;
		MemoryReader << ActorTransform;
		MemoryReader << CurrentTags;

		MemoryReader.Close();

		for (UClass* classData : classType)
		{

			if (classData->GetName().Contains(ActorName))
			{

				UE_LOG(LogTemp, Warning, TEXT("Success"));

				SpawnedActor = World->GetWorld()->SpawnActor<AActor>(classData);

				SpawnedActor->SetActorLabel(ActorName);
				SpawnedActor->SetActorTransform(ActorTransform);
				SpawnedActor->Tags = CurrentTags;

				break;
			}
			UE_LOG(LogTemp, Warning, TEXT("Failed To ClassData"));
			// Örneğin, ekrana yazdırmak için:

			//UE_LOG(LogTemp, Warning, TEXT("Byte Value: %u"), ByteValue);
		}
	}



	//if (SpawnedActor)
	//{
	//	SpawnedActor->SetActorLabel(ActorName);
	//	SpawnedActor->SetActorTransform(ActorTransform);
	//	SpawnedActor->Tags = CurrentTags;
	//}

	//return SpawnedActor;
}


TArray<uint8>  UMephistoSave::Serializeables(TArray<AActor*> MyActors)
{
	TArray<uint8> SerializedData;

	if (MyActors.Num() != 0)
	{
		FMemoryWriter MemoryWriter(SerializedData);

		for (AActor* actor : MyActors)
		{
			FString ActorName = actor->GetName();
			FTransform ActorTransform = actor->GetTransform();
			TArray<FName> ActorTags = actor->Tags;

			MemoryWriter << ActorName;
			MemoryWriter << ActorTransform;
			MemoryWriter << ActorTags;
		}

		MemoryWriter.Close();
	}

	return SerializedData;

}

bool UMephistoSave::WriteDataToFile(const FString& Directory, const FString& FileName, const TArray<FString>& Data)
{
	FString FullPath = FPaths::Combine(Directory, FileName);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FullPath, true);
	if (FileHandle)
	{
		for (const FString& Line : Data)
		{
			FString LineWithNewLine = Line + TEXT("\n");
			FileHandle->Write(reinterpret_cast<const uint8*>(*LineWithNewLine), LineWithNewLine.Len());
		}

		delete FileHandle;

		return true;
	}

	return false;
}

TArray<FString> UMephistoSave::ReadDataFromFile(const FString& Directory, const FString& FileName)
{
	TArray<FString> ReadData;

	FString FullPath = FPaths::Combine(Directory, FileName);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	IFileHandle* FileHandle = PlatformFile.OpenRead(*FullPath);
	if (FileHandle)
	{
		uint32 FileSize = FileHandle->Size();
		TArray<uint8> FileContent;
		FileContent.SetNumUninitialized(FileSize);
		FileHandle->Read(FileContent.GetData(), FileSize);

		delete FileHandle;

		FString FileContentStr = FString(reinterpret_cast<const TCHAR*>(FileContent.GetData()), FileSize);

		TArray<FString> Lines;
		FileContentStr.ParseIntoArrayLines(Lines, true);

		ReadData = MoveTemp(Lines);
	}

	return ReadData;
}

///
//bool UMephistoSave::SaveStructToFile(const FString& FilePath, const FMyStruct& Data)
//{
//	FString FileContent = FString::Printf(TEXT("%s\n%d\n"), *Data.Name, Data.Age);
//
//	return FFileHelper::SaveStringToFile(FileContent, *FilePath);
//}
//
//
//
//bool UMephistoSave::LoadStructFromFile(const FString& FilePath, FMyStruct& OutData)
//{
//	FString FileContent;
//	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
//	{
//		TArray<FString> Lines;
//		FileContent.ParseIntoArrayLines(Lines, true);
//
//		if (Lines.Num() == 2)
//		{
//			OutData.Name = Lines[0];
//			OutData.Age = FCString::Atoi(*Lines[1]);
//
//			return true;
//		}
//	}
//
//	return false;
//}