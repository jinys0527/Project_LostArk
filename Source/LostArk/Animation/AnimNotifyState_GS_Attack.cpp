// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_GS_Attack.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"
#include "../Weapon/GreatSword.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"

void UAnimNotifyState_GS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		if (UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent())
		{
			TArray<AMonster*> TargetArray = Player->Target.Array();
			for (int32 i = TargetArray.Num() - 1; i>=0; --i)
			{
				if (TargetArray[i])
				{
					if (TargetArray[i]->bIsHitted)
					{
						continue;
					}
					else if (!TargetArray[i]->bIsHitted)
					{
						TargetArray[i]->bIsHitted = true;
					}

					float Crit = FMath::FRand();
					Crit *= 100.f;
					float CritRate = Cast<ULostArkPlayerAttributeSet>(Player->GetAbilitySystemComponent()->GetAttributeSet(ULostArkPlayerAttributeSet::StaticClass()))->GetCritRate();
					if (Crit >= CritRate)
					{
						TargetArray[i]->bIsCriticaled = true;
					}
					else
					{
						TargetArray[i]->bIsCriticaled = false;
					}

					if (UAbilitySystemComponent* TargetASC = TargetArray[i]->GetAbilitySystemComponent())
					{
						FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
						EffectContext.AddInstigator(Player, Player->GetController());
						FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
						if (EffectSpecHandle.IsValid())
						{
							ASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
							TargetArray[i]->BroadcastLifePoint();
						}
					}
				}
			}
		}
	}
}