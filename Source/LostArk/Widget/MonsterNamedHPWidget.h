// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "MonsterNamedHPWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UMonsterNamedHPWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHP;

	float GetCurrentHP();

	void SetCurrentHP(int NewCurrentHP);

	float GetMaxHP();

	void SetMaxHP(int NewMaxHP);

	void SetHPBarPercent(float NewCurrentHP, float NewMaxHP);
};
