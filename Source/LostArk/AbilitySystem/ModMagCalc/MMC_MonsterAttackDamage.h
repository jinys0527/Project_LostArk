// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MonsterAttackDamage.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UMMC_MonsterAttackDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MonsterAttackDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition MonsterATKDef;
	FGameplayEffectAttributeCaptureDefinition MonsterMaxATKDef;
	FGameplayEffectAttributeCaptureDefinition BlockDef;
};
