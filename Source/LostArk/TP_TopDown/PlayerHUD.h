// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/HUD.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHP;

	void UpdateName(FString MonsterName);

	void UpdateCurrentHP(float MonsterCurrentHP);

	void SetMaxHP(float MonsterMaxHP);

	void UpdateHPBar(float Percent);

	float CalcPercent(float MonsterCurrentHP, float MonsterMaxHP);
};
