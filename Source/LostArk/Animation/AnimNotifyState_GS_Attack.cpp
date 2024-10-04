// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_GS_Attack.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"
#include "../Weapon/GreatSword.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

void UAnimNotifyState_GS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		if (UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent())
		{
			for (AMonster* Target : Player->Target)
			{
				if (Target)
				{
					if (Target->bIsHitted)
					{
						continue;
					}

					if (Target)
					{
						if(UAbilitySystemComponent* TargetASC = Target->GetAbilitySystemComponent())
						{
							FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
							EffectContext.AddInstigator(Player, Player->GetController());
							FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
							if (EffectSpecHandle.IsValid())
							{
								ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
								Target->BroadcastLifePoint();
							}
						}
					}
				}
			}
		}
	}
}