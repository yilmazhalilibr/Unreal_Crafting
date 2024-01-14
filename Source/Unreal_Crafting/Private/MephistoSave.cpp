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

// Yardımcı bir fonksiyon: Bytes dizisini FString'e dönüştürme
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

		UE_LOG(LogTemp, Warning, TEXT("Name %s"), *ActorName);

		MemoryWriter.Close();
	}

	return SerializedData;

}


AActor* UMephistoSave::Deserializeable(TArray<UClass*> classType, UWorld* World, const TArray<uint8>& SerializedData)
{

	FMemoryReader MemoryReader(SerializedData, true);

	FString ActorName;
	FTransform ActorTransform;
	TArray<FName> CurrentTags;

	MemoryReader << ActorName;
	MemoryReader << ActorTransform;
	MemoryReader << CurrentTags;

	MemoryReader.Close();


	AActor* SpawnedActor = nullptr;

	for (UClass* classData : classType)
	{

		if (classData->GetName().Contains("RightArm"))
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

	// Dosyayı yazma işlemi
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Binary dosyayı yazma modunda açma
	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FullPath, true);
	if (FileHandle)
	{
		// Verileri dosyaya yazma
		for (const FString& Line : Data)
		{
			FString LineWithNewLine = Line + TEXT("\n");
			FileHandle->Write(reinterpret_cast<const uint8*>(*LineWithNewLine), LineWithNewLine.Len());
		}

		// Dosyayı kapatma
		delete FileHandle;

		// Dosya başarıyla kaydedildi
		return true;
	}

	// Dosya açılamadı veya yazma hatası oluştu
	return false;
}

TArray<FString> UMephistoSave::ReadDataFromFile(const FString& Directory, const FString& FileName)
{
	TArray<FString> ReadData;

	FString FullPath = FPaths::Combine(Directory, FileName);

	// Dosyayı okuma işlemi
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Binary dosyasını okuma modunda açma
	IFileHandle* FileHandle = PlatformFile.OpenRead(*FullPath);
	if (FileHandle)
	{
		// Dosyayı tamamen okuma işlemi
		uint32 FileSize = FileHandle->Size();
		TArray<uint8> FileContent;
		FileContent.SetNumUninitialized(FileSize);
		FileHandle->Read(FileContent.GetData(), FileSize);

		// Dosyayı kapatma
		delete FileHandle;

		// Dosyadan okunan veriyi FString'e dönüştürme
		FString FileContentStr = FString(reinterpret_cast<const TCHAR*>(FileContent.GetData()), FileSize);

		// FString'i satırlara ayırma
		TArray<FString> Lines;
		FileContentStr.ParseIntoArrayLines(Lines, true);

		// Okunan satırları çıktı olarak döndürme
		ReadData = MoveTemp(Lines);
	}

	return ReadData;
}

