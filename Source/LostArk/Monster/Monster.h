// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/BaseCharacter.h"
#include "MonsterType.h"
#include "Monster.generated.h"

class APlayerHUD;
class UHeadMountHPWidget;
class UWidgetComponent;
class UDamageWidget;
class ABossMonster;
class ANamedMonster;

/**
 * 
 */
UCLASS()
class LOSTARK_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonster();

	FStat Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	APlayerHUD* MonsterHPBar;

	virtual void PlayDead() override;

	virtual void Attack() override;

	virtual void PlayHitReaction() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* HeadMountHPBarWidget;

	void UpdateHeadMountHP(float CurrentHP, float MaxHP);

	TSubclassOf<AMonster> CommonClass;

	TSubclassOf<ANamedMonster> NamedClass;

	TSubclassOf<ABossMonster> BossClass;

	void Death();

	uint8 bIsAttack : 1;

	uint8 bIsHitted : 1;

	float DisttoTarget;

	EMonsterType MonsterType;

	virtual void Tick(float DeltaSeconds) override;
};
