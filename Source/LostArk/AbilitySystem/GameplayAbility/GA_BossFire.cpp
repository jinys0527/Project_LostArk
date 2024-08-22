// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BossFire.h"
#include "../../Common/BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "../../Player/MyPlayer.h"
#include "../../Monster/BossMonster.h"
#include "../../Monster/MonsterAIController.h"

UGA_BossFire::UGA_BossFire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_BossFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ABaseCharacter* BaseCharacter = CastChecked<ABaseCharacter>(ActorInfo->AvatarActor.Get());
	BaseCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAbilityTask_PlayMontageAndWait* PlayBossFireTask;

	if (ABossMonster* BossMonster = Cast<ABossMonster>(BaseCharacter))
	{
		PlayBossFireTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), BossMonster->GetFireMontage(), 1.0f);
		PlayBossFireTask->OnCompleted.AddDynamic(this, &UGA_BossFire::OnCompleteCallback);
		PlayBossFireTask->OnInterrupted.AddDynamic(this, &UGA_BossFire::OnInterruptedCallback);
		PlayBossFireTask->ReadyForActivation();
	}

	if (AController* Controller = ActorInfo->AvatarActor->GetInstigatorController())
	{
		AMonsterAIController* AIController = Cast<AMonsterAIController>(Controller);
		if (AIController)
		{
			AIController->NotifyAbilityStart();
		}
	}
}

void UGA_BossFire::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_BossFire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (AController* Controller = ActorInfo->AvatarActor->GetInstigatorController())
	{
		AMonsterAIController* AIController = Cast<AMonsterAIController>(Controller);
		if (AIController)
		{
			AIController->NotifyAbilityEnd();
		}
	}
	ABaseCharacter* BaseCharacter = CastChecked<ABaseCharacter>(ActorInfo->AvatarActor.Get());
	BaseCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UGA_BossFire::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_BossFire::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
