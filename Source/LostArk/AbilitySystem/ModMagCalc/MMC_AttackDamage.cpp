// Fill out your copyright notice in the Description page of Project Settings.



#include "MMC_AttackDamage.h"
#include "../LostArkMonsterAttributeSet.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_AttackDamage::UMMC_AttackDamage()
{
	ATKDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetATKAttribute();
	ATKDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	ATKDef.bSnapshot = false;
	MaxATKDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetMaxATKAttribute();
	MaxATKDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MaxATKDef.bSnapshot = false;
	MonsterDEFDef.AttributeToCapture = ULostArkMonsterAttributeSet::GetDEFAttribute();
	MonsterDEFDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MonsterDEFDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ATKDef);
	RelevantAttributesToCapture.Add(MonsterDEFDef);
	RelevantAttributesToCapture.Add(MaxATKDef);
}

float UMMC_AttackDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float ATK = 0.0f;
	GetCapturedAttributeMagnitude(ATKDef, Spec, EvaluateParameters, ATK);
	ATK = FMath::Max(ATK, 0.0f);

	float MaxATK = 0.0f;
	GetCapturedAttributeMagnitude(MaxATKDef, Spec, EvaluateParameters, MaxATK);
	MaxATK = FMath::Max(MaxATK, 0.0f);

	float RandomDamage = FMath::RandRange(ATK, MaxATK);

	float MonsterDEF = 0.0f;
	GetCapturedAttributeMagnitude(MonsterDEFDef, Spec, EvaluateParameters, MonsterDEF);
	MonsterDEF = FMath::Max(MonsterDEF, 0.0f);
	MonsterDEF = 1.f - (MonsterDEF / (MonsterDEF + 6500.f) * 100.f);

	UE_LOG(LogTemp, Warning, TEXT("%f"), RandomDamage * MonsterDEF);

	return RandomDamage * MonsterDEF;
}
