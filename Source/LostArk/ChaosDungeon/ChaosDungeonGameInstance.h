// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ChaosDungeonGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UChaosDungeonGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	float CurrentProgress = 0.0f;
	FString ProgressValue = "0";

	float PlayerBattleLevel = 1;
	float PlayerExpeditionLevel = 1;

	float PlayerBattleEXPBarPercent = 0.0f;
	float PlayerExpeditionEXPBarPercent = 0.0f;

	float PlayerBattleEXP = 0.0f;
	float PlayerExpeditionEXP = 0.0f;
	float PlayerBattleRequiredEXP = 500.0f;
	float PlayerExpeditionRequiredEXP = 1500.0f;

	float PlayerCurrentLifePoint = 453.0f;
	float PlayerCurrentManaPoint = 793.0f;
};
