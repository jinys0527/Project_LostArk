// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stat.Dodge = 0.0f;
	Stat.HitRate = 1.0f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void ABaseCharacter::PlayDead()
{
	
}

void ABaseCharacter::PlayHitReaction()
{
}

void ABaseCharacter::Move()
{
}

void ABaseCharacter::Attack()
{
}

float ABaseCharacter::CalcDamage(float ATK, float Block)
{
	FString StrBlock = FString::Printf(TEXT(".2f"), Block);
	Block = FCString::Atof(*StrBlock);

	float FinalDamage = ATK * (Block * 100.f) / 10000.f;

	return FinalDamage;
}

