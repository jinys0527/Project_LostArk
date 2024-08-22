// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "HeadMountHPWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UHeadMountHPWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;
};
