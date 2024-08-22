// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_MaxManaPoint.h"
#include "../../Player/MyPlayer.h"

float UMMC_MaxManaPoint::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Spec.GetContext().GetSourceObject());
	const float PlayerLevel = MyPlayer->GetPlayerLevel();
	return 793 + 49.48 * (PlayerLevel - 1.0f);
}
