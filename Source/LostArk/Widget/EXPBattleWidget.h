// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "EXPBattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UEXPBattleWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* BattleEXPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BattleLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExpeditionLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEXPExpeditionWidget* EXPExpeditionWidget;

	void UpdateBattleLevel(float NewBattleLevel);
	void UpdateExpeditionLevel(float NewExpeditionLevel);
};
