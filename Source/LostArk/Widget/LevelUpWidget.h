// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */

class UWidgetAnimation;

UCLASS()
class LOSTARK_API ULevelUpWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* LevelUp;
};
