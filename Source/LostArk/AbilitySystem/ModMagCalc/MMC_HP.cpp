// Fill out your copyright notice in the Description page of Project Settings.


#include "MMC_HP.h"
#include "../../Player/MyPlayer.h"

float UMMC_HP::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Spec.GetContext().GetSourceObject());
	float PlayerLevel = MyPlayer->GetPlayerLevel();
	return 206 + (4.56 * (PlayerLevel - 1.0f));
}
