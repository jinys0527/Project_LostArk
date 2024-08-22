// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "MonsterBossHPWidget.generated.h"


class UProgressBar;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class LOSTARK_API UMonsterBossHPWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Mark;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHP;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHP;

	uint8 bIsCreated : 1;

	uint8 bIsAlive : 1;

	virtual void NativeConstruct() override;

};
