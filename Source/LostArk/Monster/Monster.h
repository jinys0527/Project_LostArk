// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/BaseCharacter.h"
#include "../Widget/OverlayWidgetController.h"
#include "MonsterType.h"
#include "Monster.generated.h"

class APlayerHUD;
class UHeadMountHPWidget;
class UWidgetComponent;
class UDamageWidget;
class ABossMonster;
class ANamedMonster;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimInstance_Monster;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterDeadWithType, EMonsterType, NewMonsterType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterDeadWithMonster, AMonster*, Monster);

/**
 * 
 */
UCLASS()
class LOSTARK_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonster();

	virtual void PlayDead() override;

	virtual void Attack() override;

	virtual void PlayHitReaction() override;

	virtual void PossessedBy(AController* NewController);

	UFUNCTION()
	virtual void OnOutOfHealth();

	UFUNCTION()
	virtual void OnGetDamage(AActor* DamageCauser, float Damage);

	virtual void SetDead();

	virtual void InitAbilityActorInfo() override;

	virtual void BroadcastLifePoint();

	void SetDamageWidgetColor();

protected:
	virtual void BeginPlay() override;

	
private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffect")
	TSubclassOf<class UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	TSubclassOf<class AController> MonsterAIControllerClass;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMonsterCurrentLifePointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMonsterMaxLifePointChanged;

	UAnimInstance_Monster* AnimInstance;

	FOnMonsterDead OnMonsterDead;

	FOnMonsterDeadWithType OnMonsterDeadWithType;

	FOnMonsterDeadWithMonster OnMonsterDeadWithMonster;

	float DeadEventDelayTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayAbility> AttackAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* HeadMountHPBarWidget;

	uint8 bIsAttack : 1;

	uint8 bIsHitted : 1;

	uint8 bIsCriticaled : 1;

	float DisttoTarget;

	AActor* Target;

	EMonsterType MonsterType;

	UUserWidget* MiniMapWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	APlayerHUD* MonsterHPBar;

};
