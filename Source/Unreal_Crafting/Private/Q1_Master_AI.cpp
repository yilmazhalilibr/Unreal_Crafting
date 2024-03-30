// Fill out your copyright notice in the Description page of Project Settings.


#include "Q1_Master_AI.h"

// Sets default values
AQ1_Master_AI::AQ1_Master_AI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQ1_Master_AI::BeginPlay()
{
	Super::BeginPlay();

	CurrentAIState = EAIState::Idle;

}

// Called every frame
void AQ1_Master_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAIState();
}

// Called to bind functionality to input
void AQ1_Master_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Update AI state based on conditions
void AQ1_Master_AI::UpdateAIState()
{
	switch (CurrentAIState)
	{
	case EAIState::Idle:
		Idle();
		break;
	case EAIState::Patrol:
		Patrol();
		break;
	case EAIState::Follow:
		Follow();
		break;
	case EAIState::Attack:
		Attack();
		break;
	case EAIState::Dead:
		Dead();
		break;
	default:
		break;
	}
}

// AI State functions
void AQ1_Master_AI::Idle()
{
	// Implement Idle state behavior here
}

void AQ1_Master_AI::Patrol()
{
	// Implement Patrol state behavior here
}

void AQ1_Master_AI::Follow()
{
	// Implement Follow state behavior here
}

void AQ1_Master_AI::Attack()
{
	// Implement Attack state behavior here
}

void AQ1_Master_AI::Dead()
{
	// Implement Dead state behavior here
}