// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_SkillCooldownDecrease.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_SkillCooldownDecrease::UMMC_SkillCooldownDecrease()
{
	SwiftnessDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetSwiftnessAttribute();
	SwiftnessDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SwiftnessDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(SwiftnessDef);
}

float UMMC_SkillCooldownDecrease::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Swiftness = 0.0f;
	GetCapturedAttributeMagnitude(SwiftnessDef, Spec, EvaluateParameters, Swiftness);
	Swiftness = FMath::Max<float>(Swiftness, 0.0f);
	return Swiftness / 46.568;
}
