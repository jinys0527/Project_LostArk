// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_DebuffTimeBonus.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_DebuffTimeBonus::UMMC_DebuffTimeBonus()
{
	ExpertiseDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetExpertiseAttribute();
	ExpertiseDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ExpertiseDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ExpertiseDef);
}

float UMMC_DebuffTimeBonus::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Expertise = 0.0f;
	GetCapturedAttributeMagnitude(ExpertiseDef, Spec, EvaluateParameters, Expertise);
	Expertise = FMath::Max<float>(Expertise, 0.0f);
	return Expertise / 23.29;
}
