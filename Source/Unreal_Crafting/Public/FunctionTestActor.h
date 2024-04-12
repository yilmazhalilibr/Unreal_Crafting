// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MephistoFunctions.h"
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

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void CalculateExample();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
