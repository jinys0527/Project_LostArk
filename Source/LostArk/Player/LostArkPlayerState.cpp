// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkPlayerState.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"

ALostArkPlayerState::ALostArkPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULostArkAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULostArkPlayerAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void ALostArkPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostArkPlayerState, Level);
}

UAbilitySystemComponent* ALostArkPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALostArkPlayerState::OnRep_Level(float OldLevel)
{
	//UI
	//»ç¿îµå
}
