// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionTestActor.h"

// Sets default values
AFunctionTestActor::AFunctionTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AFunctionTestActor::~AFunctionTestActor()
{
	delete MephistoClassPtr;
}

// Called when the game starts or when spawned
void AFunctionTestActor::BeginPlay()
{
	Super::BeginPlay();

	OperatorOverloading k = OperatorOverloading(231, 25);
	k.Print();
	OperatorOverloading k1(11, 11);
	OperatorOverloading k2(-999, -999);
	k = k1 + k2;
	k.Print();


	InheritanceTest InTest{ "Halil", "YILMAZ", 66 };
	FString HappyString(InTest.GetProperties().c_str());
	UE_LOG(LogTemp, Warning, TEXT("Inheritance Data Name: %s"), *HappyString);
}

void AFunctionTestActor::CalculateExample(float x, int y, float z, float& OutputResult, float& OutputPlus, bool& isSuccess)
{

	MephistoClassPtr->CalculateAllCounts(x, y, z, OutputResult);
	ResultValue = MephistoClassPtr->constDeger;

}

void AFunctionTestActor::ReturnResult(float x, float& value)
{
	ResultValue = x;
}

// Called every frame
void AFunctionTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

