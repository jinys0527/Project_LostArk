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

	void UpdateHPBar(float NamedCurrentHP, float NamedMaxHP);

	void UpdateName(FString NewName);

	UFUNCTION()
	FString GetName();

	UFUNCTION()
	float GetCurrentHP();

	UFUNCTION()
	float GetMaxHP();

	void SetCurrentHP(float NamedCurrentHP);

	void SetMaxHP(float NamedMaxHP);
};
