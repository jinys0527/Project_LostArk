// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_MonsterAttackDamage.h"
#include "../LostArkMonsterAttributeSet.h"
#include "../LostArkPlayerAttributeSet.h"

UMMC_MonsterAttackDamage::UMMC_MonsterAttackDamage()
{
	MonsterATKDef.AttributeToCapture = ULostArkMonsterAttributeSet::GetATKAttribute();
	MonsterATKDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MonsterATKDef.bSnapshot = false;
	MonsterMaxATKDef.AttributeToCapture = ULostArkMonsterAttributeSet::GetMaxATKAttribute();
	MonsterMaxATKDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MonsterMaxATKDef.bSnapshot = false;
	BlockDef.AttributeToCapture = ULostArkPlayerAttributeSet::GetBlockAttribute();
	BlockDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	BlockDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(MonsterATKDef);
	RelevantAttributesToCapture.Add(MonsterMaxATKDef);
	RelevantAttributesToCapture.Add(BlockDef);
}

float UMMC_MonsterAttackDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float MonsterATK = 0.0f;
	GetCapturedAttributeMagnitude(MonsterATKDef, Spec, EvaluateParameters, MonsterATK);
	MonsterATK = FMath::Max(MonsterATK, 0.0f);
	
	float MonsterMaxATK = 0.0f;
	GetCapturedAttributeMagnitude(MonsterMaxATKDef, Spec, EvaluateParameters, MonsterMaxATK);
	MonsterMaxATK = FMath::Max(MonsterMaxATK, 0.0f);

	float RandomDamage = FMath::RandRange(MonsterATK, MonsterMaxATK);

	float Block = 0.0f;
	GetCapturedAttributeMagnitude(BlockDef, Spec, EvaluateParameters, Block);
	Block = FMath::Max(Block, 0.0f);

	return RandomDamage * (1.f - (Block / 100.f));
}
