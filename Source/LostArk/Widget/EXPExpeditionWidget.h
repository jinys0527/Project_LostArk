// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "EXPExpeditionWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UEXPExpeditionWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ExpeditionEXPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BattleLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExpeditionLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEXPBattleWidget* EXPBattleWidget;

	void UpdateBattleLevel(float NewBattleLevel);
	void UpdateExpeditionLevel(float NewExpeditionLevel);
};
