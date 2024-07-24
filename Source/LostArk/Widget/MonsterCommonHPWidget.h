// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterCommonHPWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UMonsterCommonHPWidget : public UUserWidget
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
	
	void UpdateHPBar(float CommmonCurrentHP, float CommmonMaxHP);

	void UpdateName(FString NewName);

	UFUNCTION()
	FString GetName();

	UFUNCTION()
	float GetCurrentHP();

	UFUNCTION()
	float GetMaxHP();

	void SetCurrentHP(float CommmonCurrentHP);

	void SetMaxHP(float CommmonMaxHP);
};
