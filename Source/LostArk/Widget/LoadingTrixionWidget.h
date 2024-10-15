// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "LoadingWidget.h"
#include "LoadingTrixionWidget.generated.h"


class UProgressBar;
class USlider;

/**
 * 
 */
UCLASS()
class LOSTARK_API ULoadingTrixionWidget : public ULoadingWidget
{
	GENERATED_BODY()
	
public:
	ULoadingTrixionWidget();

	virtual void Loading();

	virtual void Loopback();

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* LoadingGauge;

	UPROPERTY(meta = (BindWidget))
	USlider* LoadingGaugeArrow;
};
