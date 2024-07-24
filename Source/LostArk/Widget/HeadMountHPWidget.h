// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeadMountHPWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UHeadMountHPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPBar;

	void UpdateHPBar(float MonsterCurrentHP, float MonsterMaxHP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DesiredSize")
	FVector2D DesiredSize;

	virtual void SynchronizeProperties() override;
};
