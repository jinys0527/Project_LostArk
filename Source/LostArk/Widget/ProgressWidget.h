// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Monster/MonsterType.h"
#include "ProgressWidget.generated.h"

class UProgressBar;
class UButton;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UProgressWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ChaosDungeonProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ProgressValue;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Percent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Highlight;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Exit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Toggle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Line;

	void UpdateProgress(EMonsterType MonsterType);
};
