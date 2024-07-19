// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Monster.generated.h"

class APlayerHUD;
class UHeadMountHPWidget;
class UWidgetComponent;

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

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UHPWidget> HPWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UHeadMountHPWidget* HeadMountHPWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<UHeadMountHPWidget> HeadMountHPWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* HeadMountHPBarWidget;*/

	virtual void PlayDead();

	virtual void PlayHitReaction();

	virtual void Move();

	virtual void Attack();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BeginPlay() override;
};
