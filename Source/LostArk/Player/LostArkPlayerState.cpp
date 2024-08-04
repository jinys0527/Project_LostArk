// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkPlayerState.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkAttributeSet.h"

ALostArkPlayerState::ALostArkPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULostArkAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULostArkAttributeSet>(TEXT("AttributeSet"));
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ALostArkPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
