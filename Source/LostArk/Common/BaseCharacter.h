// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stat.h"
#include "BaseCharacter.generated.h"

class UAnimMontage;
class UAnimationAsset;
class UDamageWidget;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Moving,
	Battle,
	Attacking,
	Dashing,
	Stunned,
	Skilling,
	GetHitting,
	Down,
	Death
};

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

	//������(UGameplayStatics::ApplyDamage), �´´�(APawn::TakeDamage, PlayHitReaction), �״´�(PlayDead), �̵��Ѵ�(Move), ��ų�� �÷��̾�?
	//Stat
	//�ִϸ��̼�(Attack, HitReaction, Dead, Move)

	FStat Stat;

	FString Name;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> DamageClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	UDamageWidget* wDamage;

	FVector WidgetLocation;
	
	uint8 isAlive : 1;
};