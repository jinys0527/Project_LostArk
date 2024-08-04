// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArkUserWidget.h"
#include "PlayerSlotWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class LOSTARK_API UPlayerSlotWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerSlot;
};
