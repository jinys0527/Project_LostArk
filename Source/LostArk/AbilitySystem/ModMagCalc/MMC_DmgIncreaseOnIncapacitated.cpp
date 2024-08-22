// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_DmgIncreaseOnIncapacitated.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_DmgIncreaseOnIncapacitated::UMMC_DmgIncreaseOnIncapacitated()
{
	DominationDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetDominationAttribute();
	DominationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DominationDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(DominationDef);
}

float UMMC_DmgIncreaseOnIncapacitated::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Domination = 0.0f;
	GetCapturedAttributeMagnitude(DominationDef, Spec, EvaluateParameters, Domination);
	Domination = FMath::Max<float>(Domination, 0.0f);
	return Domination / 16.3;
}
