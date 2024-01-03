// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SCharacter.h"

// Sets default values
ACPP_SCharacter::ACPP_SCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereComponent->SetMobility(EComponentMobility::Movable);

}

// Called when the game starts or when spawned
void ACPP_SCharacter::BeginPlay()
{
	Super::BeginPlay();
	FVector newLocation = FVector(150.0f, 0.f, 0.f);
	SphereComponent->SetWorldLocation(newLocation);
}

// Called every frame
void ACPP_SCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_SCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_SCharacter::FindPath(UPrimitiveComponent* Collision)
{
	FHitResult HitResult;
	FVector collisionSt = Collision->GetComponentLocation();
	FVector collisionEnd = FVector(0.f, 0.f, 0.f);
	FCollisionQueryParams CollisionParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, collisionSt, collisionEnd, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		DrawDebugLine(GetWorld(), collisionSt, collisionEnd, FColor::Red, false, 15.0f, 0, 5.0f);

		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			AStaticMeshActor* HitStaticMeshActor = Cast<AStaticMeshActor>(HitActor);

			if (HitStaticMeshActor)
			{
				FVector moveTo = HitActor->GetActorLocation();
				SetActorLocation(moveTo);
			}
		}

	}


}
