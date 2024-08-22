// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_ATK.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_ATK::UMMC_ATK()
{
	AbilityDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetAbilityAttribute();
	AbilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AbilityDef.bSnapshot = false;
	WeaponATKDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetWeaponATKAttribute();
	WeaponATKDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	WeaponATKDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(AbilityDef);
	RelevantAttributesToCapture.Add(WeaponATKDef);
}

float UMMC_ATK::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Ability = 0.0f;
	GetCapturedAttributeMagnitude(AbilityDef, Spec, EvaluateParameters, Ability);
	Ability = FMath::Max(Ability, 0.0f);

	float WeaponATK = 0.0f;
	GetCapturedAttributeMagnitude(WeaponATKDef, Spec, EvaluateParameters, WeaponATK);
	WeaponATK = FMath::Max(WeaponATK, 0.0f);

	return  float(FMath::Sqrt(((double)Ability * (double)WeaponATK) / (double)6));
}
