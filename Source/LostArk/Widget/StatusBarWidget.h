// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "StatusBarWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UStatusBarWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Time")
	FText GetCurrentTime() const;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentTime;

	virtual void NativeConstruct() override;

	FTimerHandle TimerHandle;

	void UpdateTime();
};
