// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stat.h"
#include "BaseCharacter.generated.h"

class UAnimMontage;
class UAnimationAsset;

UCLASS()
class LOSTARK_API ABaseCharacter : public ACharacter
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

	//때린다(UGameplayStatics::ApplyDamage), 맞는다(APawn::TakeDamage, PlayHitReaction), 죽는다(PlayDead), 이동한다(Move), 스킬은 플레이어?
	//Stat
	//애니메이션(Attack, HitReaction, Dead, Move)

	FStat Stat;

	FString Name;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimationAsset> IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> HitReactionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> MoveMontage;

	UFUNCTION(BlueprintCallable)
	virtual void PlayDead();

	UFUNCTION(BlueprintCallable)
	virtual void PlayHitReaction();

	UFUNCTION(BlueprintCallable)
	virtual void Move();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	float CalcDamage(float ATK, float Block);
};