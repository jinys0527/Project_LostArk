// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "OverlayWidget.generated.h"

class UHeadMountHPWidget;
class UMonsterBossHPWidget;
class UMonsterCommonHPWidget;
class UMonsterNamedHPWidget;
class UPlayerSlotWidget;
class UPlayerStatusWidget;
class UProgressWidget;
class UTimerWidget;
class UEXPBattleWidget;
class UEXPExpeditionWidget;
class UEXPBattleWidget;
class UChatWidget;
class UStatusBarWidget;
class UMinimapTrixionWidget;
class UMinimapLogHillWidget;

/**
 * 
 */
UCLASS()
class LOSTARK_API UOverlayWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<ULostArkUserWidget> BossHPClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMonsterBossHPWidget* WBPHPBoss;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> CommonHPClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMonsterCommonHPWidget* WBPHPCommon;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> NamedHPClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMonsterNamedHPWidget* WBPHPNamed;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerSlotClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPlayerSlotWidget* WBPPlayerSlot;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerStatusClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPlayerStatusWidget* WBPPlayerStatus;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ProgressClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressWidget* WBPProgress;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> TimerClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTimerWidget* WBPTimer;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> EXPBattleClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEXPBattleWidget* WBPExpBattle;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ExpExpeditionClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEXPExpeditionWidget* WBPExpExpedition;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ChatClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UChatWidget* WBPChat;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> StatusBarClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UStatusBarWidget* WBPStatusBar;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MinimapTrixionClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMinimapTrixionWidget* WBPMiniMapTrixion;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MinimapLogHillClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMinimapLogHillWidget* WBPMiniMapLogHill;
};
