// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Attack.h"
#include "../../Common/BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "../../Player/MyPlayer.h"
#include "../../Monster/Monster.h"
//#include ""

UGA_Attack::UGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ABaseCharacter* BaseCharacter = CastChecked<ABaseCharacter>(ActorInfo->AvatarActor.Get());
	UAbilityTask_PlayMontageAndWait* PlayAttackTask;
	if (AMyPlayer* MyPlayer = Cast<AMyPlayer>(BaseCharacter))
	{
		if (!MyPlayer->bIsEquipped)
		{
			PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayEquip"), MyPlayer->GetEquipMontage(), 1.0f);
			MyPlayer->bIsEquipped = true;
			MyPlayer->TimeCount = 0;
			GetWorld()->GetTimerManager().SetTimer(MyPlayer->StepHandle, MyPlayer, &AMyPlayer::OnTimer, 1.0f, true);
			PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_Attack::OnCompleteCallback);
			PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_Attack::OnInterruptedCallback);
			PlayAttackTask->ReadyForActivation();
		}
		else
		{
			BaseCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			int32 RandomNumber = FMath::RandRange(1, 3);
			FString SectionName = FString::Printf(TEXT("Attack_%d"), RandomNumber);
			PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), BaseCharacter->GetAttackMontage(), 1.0f, *SectionName);
			MyPlayer->TimeCount = 0;
			PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_Attack::OnCompleteCallback);
			PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_Attack::OnInterruptedCallback);
			PlayAttackTask->ReadyForActivation();
		}
	}

	if(AMonster* Monster = Cast<AMonster>(BaseCharacter))
	{
		BaseCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), Monster->GetAttackMontage(), 1.0f);
		PlayAttackTask->OnCompleted.AddDynamic(this, &UGA_Attack::OnCompleteCallback);
		PlayAttackTask->OnInterrupted.AddDynamic(this, &UGA_Attack::OnInterruptedCallback);
		PlayAttackTask->ReadyForActivation();
	}
}

void UGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{

}

void UGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	ABaseCharacter* BaseCharacter = CastChecked<ABaseCharacter>(ActorInfo->AvatarActor.Get());
	BaseCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UGA_Attack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
