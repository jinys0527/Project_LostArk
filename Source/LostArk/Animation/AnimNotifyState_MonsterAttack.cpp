// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_MonsterAttack.h"
#include "../Monster/Monster.h"
#include "../Player/MyPlayer.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

void UAnimNotifyState_MonsterAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	if (Monster)
	{
		if (UAbilitySystemComponent* ASC = Monster->GetAbilitySystemComponent())
		{
			AMyPlayer* MyPlayer = Cast<AMyPlayer>(Monster->Target);
			if (MyPlayer)
			{
				UAbilitySystemComponent* TargetASC = MyPlayer->GetAbilitySystemComponent();
				if (TargetASC)
				{
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					EffectContext.AddInstigator(Monster, Monster->GetController());
					FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
					if (EffectSpecHandle.IsValid())
					{
						ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
					}
				}
			}	
		}
	}
}

void UAnimNotifyState_MonsterAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	if (Monster)
	{
		if (UAbilitySystemComponent* ASC = Monster->GetAbilitySystemComponent())
		{
			if (ActiveEffectHandle.IsValid())
			{
				ASC->RemoveActiveGameplayEffect(ActiveEffectHandle);
			}
		}
	}
}
