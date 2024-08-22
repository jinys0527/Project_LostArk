// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../Widget/DamageWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ABaseCharacter::SetDead()
{
	isAlive = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDead();
	SetActorEnableCollision(false);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::InitAbilityActorInfo()
{
}

void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float CurrentLevel) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, CurrentLevel, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
	UE_LOG(LogTemp, Log, TEXT("GameplayEffect Applied Successfully"));
}

void ABaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, Level);
	ApplyEffectToSelf(DefaultSecondaryAttributes, Level);
	ApplyEffectToSelf(DefaultVitalAttributes, Level);
}