// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "PlayerStatusWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UPlayerStatusWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* MPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentMP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxMP;

	void UpdateHPBar(float PlayerCurrentHP, float PlayerMaxHP);

	void UpdateMPBar(float PlayerCurrentMP, float PlayerMaxMP);

	void SetCurrentHP(float PlayerCurrentHP);
	
	void SetMaxHP(float PlayerMaxHP);

	void SetCurrentMP(float PlayerCurrentMP);

	void SetMaxMP(float PlayerMaxMP);

	float GetCurrentHP();

	float GetMaxHP();

	float GetCurrentMP();

	float GetMaxMP();
};
