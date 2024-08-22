// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_Berserker.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_Berserker::UMMC_Berserker()
{
	SpecializationDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetSpecializationAttribute();
	SpecializationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SpecializationDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(SpecializationDef);
}

float UMMC_Berserker::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Specialization = 0.0f;
	GetCapturedAttributeMagnitude(SpecializationDef, Spec, EvaluateParameters, Specialization);
	Specialization = FMath::Max<float>(Specialization, 0.0f);

	return Specialization/699;
}
