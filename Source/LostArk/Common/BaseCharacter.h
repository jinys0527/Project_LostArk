// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UAnimMontage;
class UAnimationAsset;
class UDamageWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Moving,
	Battle,
	Attacking,
	Combat,	
	Dashing,
	Stunned,
	Skilling,
	GetHitting,
	Down,
	Death
};

UCLASS()
class LOSTARK_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> HitReactionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	UFUNCTION(BlueprintCallable)
	virtual void PlayDead();

	UFUNCTION(BlueprintCallable)
	virtual void PlayHitReaction();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	float CalcDamage(float ATK, float Block);

	virtual void SetDead();

	FORCEINLINE virtual class UAnimMontage* GetAttackMontage() const { return AttackMontage; }

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> DamageClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	UDamageWidget* wDamage;

	FVector WidgetLocation;
	
	uint8 isAlive : 1;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	float Level = 1.0f;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float CurrentLevel) const;

	void InitializeDefaultAttributes() const;
};