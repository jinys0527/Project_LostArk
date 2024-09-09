// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "RevivalWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class LOSTARK_API URevivalWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Min;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Sec;

	UPROPERTY(BlueprintReadOnly)
	int Minute;

	UPROPERTY(BlueprintReadOnly)
	int Second;

	UFUNCTION(BlueprintCallable)
	void UpdateTime(int Time);
};
