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
class ULostArkUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidget;
class UEXPExpeditionWidget;
class UMinimapTrixionWidget;
class UMinimapLogHillWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class LOSTARK_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();

	UPROPERTY()
	TObjectPtr<UOverlayWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	virtual void DrawHUD() override;

	UPROPERTY()
	UHeadMountHPWidget* HeadMountHP;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<ULostArkUserWidget> BossHPClass;

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

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ExpBattleClass;

	UPROPERTY()
	class UEXPBattleWidget* WBPExpBattle;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ExpExpeditionClass;

	UPROPERTY()
	UEXPExpeditionWidget* WBPExpExpedition;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MinimapTrixionClass;

	UPROPERTY()
	UMinimapTrixionWidget* WBPMiniMapTrixion;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> MinimapLogHillClass;

	UPROPERTY()
	UMinimapLogHillWidget* WBPMiniMapLogHill;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> RevivalClass;

	UPROPERTY()
	class URevivalWidget* WBPRevival;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ULostArkUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};