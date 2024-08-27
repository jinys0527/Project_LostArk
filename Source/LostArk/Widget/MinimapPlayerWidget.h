// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "MinimapPlayerWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class LOSTARK_API UMinimapPlayerWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UImage* Player;
};
