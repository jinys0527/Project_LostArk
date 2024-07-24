// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class LOSTARK_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DamageValue;

	void UpdateDamage(int32 Damage);

	void SetDamage(int32 Damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DesiredSize")
	FVector2D DesiredSize;

	virtual void SynchronizeProperties() override;
};
