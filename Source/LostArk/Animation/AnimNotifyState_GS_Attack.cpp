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

	if(Player)
	{ 
		if (UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent())
		{
			for (AActor* Target : Player->Target)
			{
				AMonster* Monster = Cast<AMonster>(Target);
				if (Monster)
				{
					if (Monster->bIsHitted)
					{
						continue;  
					}

					UAbilitySystemComponent* TargetASC = Monster->GetAbilitySystemComponent();
					if (TargetASC)
					{
						FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
						EffectContext.AddInstigator(Player, Player->GetController());
						FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
						if (EffectSpecHandle.IsValid())	
						{
							ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
						}
					}
				}
			}
		}
	}
}