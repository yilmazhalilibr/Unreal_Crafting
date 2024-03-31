// Fill out your copyright notice in the Description page of Project Settings.


#include "Q1_Master_AI.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

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
		Idle();
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
	// Oyuncu pawn'ını bul
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			// Hedef oyuncu pawn'ına doğru hareket et
			AIController->MoveToActor(PlayerPawn);
		}
	}
	else
	{
		// Oyuncu pawn'ı bulunamadığına dair hata işleme kodu
	}
}

void AQ1_Master_AI::Attack()
{
	// Implement Attack state behavior here

	//
	FString MyString = TEXT("Attacking!"); // Yazdırmak istediğiniz metin
	float Duration = 5.0f; // Mesajın ekran üzerinde kalacağı süre (saniye cinsinden)
	FColor Color = FColor::Green; // Mesaj rengi (isteğe bağlı)

	GEngine->AddOnScreenDebugMessage(-1, Duration, Color, MyString);
}

void AQ1_Master_AI::Dead()
{
	ACharacter::GetMovementComponent()->StopMovementImmediately();
	GetController()->StopMovement();

	// Fizik simulasyonunu başlat ve AI'ı yere düşür
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}