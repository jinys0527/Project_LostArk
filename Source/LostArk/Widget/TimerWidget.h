// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "TimerWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UTimerWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Min;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Sec;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeInfo;

	void UpdateTime();

	void InitTime();

	void StartTimer();

	uint8 bIsEnd : 1;

	FTimerHandle StageTimer;
};
