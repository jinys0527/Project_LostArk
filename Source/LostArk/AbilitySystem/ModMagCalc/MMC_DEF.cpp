// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_DEF.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_DEF::UMMC_DEF()
{
	EnduranceDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetEnduranceAttribute();
	EnduranceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnduranceDef.bSnapshot = false;
	DEFDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetPhyDEFAttribute();
	DEFDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DEFDef.bSnapshot = false;
	ArmorDEFDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetArmorDEFAttribute();
	ArmorDEFDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ArmorDEFDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(EnduranceDef);
	RelevantAttributesToCapture.Add(DEFDef);
	RelevantAttributesToCapture.Add(ArmorDEFDef);
}

float UMMC_DEF::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Endurance = 0.0f;
	GetCapturedAttributeMagnitude(EnduranceDef, Spec, EvaluateParameters, Endurance);
	Endurance = FMath::Max<float>(Endurance, 0.0f);

	float DEF = 0.0f;
	GetCapturedAttributeMagnitude(DEFDef, Spec, EvaluateParameters, DEF);
	DEF = FMath::Max<float>(DEF, 0.0f);

	float ArmorDEF = 0.0f;
	GetCapturedAttributeMagnitude(ArmorDEFDef, Spec, EvaluateParameters, ArmorDEF);
	ArmorDEF = FMath::Max<float>(ArmorDEF, 0.0f);
	DEF = 1.1 * ArmorDEF;

	return DEF + (DEF * Endurance / 12.225 / 100);
}
