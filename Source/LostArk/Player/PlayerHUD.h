// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/HUD.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UHeadMountHPWidget;
class UMonsterBossHPWidget;
class UMonsterCommonHPWidget;
class UMonsterNamedHPWidget;
class UPlayerSlotWidget;
class UPlayerStatusWidget;
class UProgressWidget;
class UTimerWidget;
/**
 * 
 */
UCLASS()
class LOSTARK_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> HeadMountClass;

	UPROPERTY()
	UHeadMountHPWidget* HeadMountHP;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> BossHPClass;

	UPROPERTY()
	UMonsterBossHPWidget* BossHP;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> CommonHPClass;

	UPROPERTY()
	UMonsterCommonHPWidget* CommonHP;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> NamedHPClass;

	UPROPERTY()
	UMonsterNamedHPWidget* NamedHP;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerSlotClass;

	UPROPERTY()
	UPlayerSlotWidget* PlayerSlot;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerStatusClass;

	UPROPERTY()
	UPlayerStatusWidget* PlayerStatus;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ProgressClass;

	UPROPERTY()
	UProgressWidget* Progress;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> TimerClass;

	UPROPERTY()
	UTimerWidget* Timer;

	virtual void DrawHUD() override;
};