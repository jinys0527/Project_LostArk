// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_AttackDamage.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UMMC_AttackDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_AttackDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition ATKDef;
	FGameplayEffectAttributeCaptureDefinition MaxATKDef;
	FGameplayEffectAttributeCaptureDefinition MonsterDEFDef;
};
