// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_CritRate.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_CritRate::UMMC_CritRate()
{
	CritDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetCritAttribute();
	CritDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	CritDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(CritDef);
}

float UMMC_CritRate::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Crit = 0.0f;
	GetCapturedAttributeMagnitude(CritDef, Spec, EvaluateParameters, Crit);
	Crit = FMath::Max<float>(Crit, 0.0f);

	return Crit/27.94;
}
