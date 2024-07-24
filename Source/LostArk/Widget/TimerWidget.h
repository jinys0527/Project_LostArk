// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeInfo;

	void UpdateTime(float NewTime);
};