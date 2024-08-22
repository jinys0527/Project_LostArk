// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_DmgIncreaseOnIncapacitated.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UMMC_DmgIncreaseOnIncapacitated : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_DmgIncreaseOnIncapacitated();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition DominationDef;
};
