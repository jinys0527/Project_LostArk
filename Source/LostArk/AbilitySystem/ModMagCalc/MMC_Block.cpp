// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Block.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_Block::UMMC_Block()
{
	DEFDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetPhyDEFAttribute();
	DEFDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DEFDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(DEFDef);
}

float UMMC_Block::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float DEF = 0.0f;
	GetCapturedAttributeMagnitude(DEFDef, Spec, EvaluateParameters, DEF);
	DEF = FMath::Max<float>(DEF, 0.0f); 

	return (DEF/(DEF + 6500.f)) * 100.f;
}
