// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Q1_Master_AI.generated.h"


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Patrol UMETA(DisplayName = "Patrol"),
	Follow UMETA(DisplayName = "Follow"),
	Attack UMETA(DisplayName = "Attack"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class UNREAL_CRAFTING_API AQ1_Master_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQ1_Master_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// AI functions
	void UpdateAIState();
	void Idle();
	void Patrol();
	void Follow();
	void Attack();
	void Dead();


	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EAIState CurrentAIState;

	// Other AI related variables and functions can be added here
	FTimerHandle MoveTimerHandle; // Zamanlayıcı tanımı
	const float PatrolRadius = 1000.0f;
};
