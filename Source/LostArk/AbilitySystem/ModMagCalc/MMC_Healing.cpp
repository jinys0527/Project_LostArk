// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_Healing.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_Healing::UMMC_Healing()
{
	EnduranceDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetEnduranceAttribute();
	EnduranceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnduranceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(EnduranceDef);
}

float UMMC_Healing::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Endurance = 0.0f;
	GetCapturedAttributeMagnitude(EnduranceDef, Spec, EvaluateParameters, Endurance);
	Endurance = FMath::Max<float>(Endurance, 0.0f);
	return Endurance / 57.943;
}
