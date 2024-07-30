// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/DamageWidget.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stat.Dodge = 0.0f;
	Stat.HitRate = 1.0f;

	static ConstructorHelpers::FClassFinder<UDamageWidget> DamageBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Widget/WB_Damage'"));
	if (DamageBlueprint.Class)
	{
		DamageClass = DamageBlueprint.Class;
	}

	isAlive = true;
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

void ABaseCharacter::Attack()
{
}

float ABaseCharacter::CalcDamage(float ATK, float Block)
{
	float FinalDamage = ATK * Block / 100.f;

	return FinalDamage;
}