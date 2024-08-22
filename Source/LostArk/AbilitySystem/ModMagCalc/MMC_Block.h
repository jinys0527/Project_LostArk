// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Block.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UMMC_Block : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_Block();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition DEFDef;
};
