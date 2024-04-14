// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MephistoFunctions.h"
#include "OperatorOverloading.h"
#include "FunctionTestActor.generated.h"

UCLASS()
class UNREAL_CRAFTING_API AFunctionTestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFunctionTestActor();
	~AFunctionTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResultValue;

	MephistoFunctions* MephistoClassPtr = new MephistoFunctions();
	MephistoFunctions* MephistoClassPtr2 = new MephistoFunctions(25, ResultValue);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void CalculateExample(float x, int y, float z, float& OutputResult, float& OutputPlus, bool& isSuccess);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void CalculateExample2() { MephistoClassPtr->CalculateAllCounts(1, 2, 3, ResultValue); };

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ReturnResult(float x, float& value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
