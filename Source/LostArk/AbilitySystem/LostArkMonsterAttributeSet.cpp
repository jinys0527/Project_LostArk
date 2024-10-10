// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkMonsterAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../Tag/LostArkGameplayTag.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"
#include "../Widget/DamageWidget.h"
#include "Components/TextBlock.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"

ULostArkMonsterAttributeSet::ULostArkMonsterAttributeSet()
{

}

void ULostArkMonsterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*
	 * Primary Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, EXP, COND_None, REPNOTIFY_Always);

	/*
	 * Secondary Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, MonsterMaxLifePoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, ATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, MaxATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, DEF, COND_None, REPNOTIFY_Always);

	/*
	 * Vital Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, MonsterCurrentLifePoint, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkMonsterAttributeSet, Damage, COND_None, REPNOTIFY_Always);
}

void ULostArkMonsterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void ULostArkMonsterAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//Source = causer of the effect, Target = target of the effect (owner of this AS)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}

}

void ULostArkMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;
	if (Data.EvaluatedData.Attribute == GetMonsterCurrentLifePointAttribute())
	{
		SetMonsterCurrentLifePoint(FMath::Clamp(GetMonsterCurrentLifePoint(), MinimumHealth, GetMonsterMaxLifePoint()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AActor* InstigatorActor = nullptr;

		if (Data.EffectSpec.GetContext().GetInstigator())
		{
			InstigatorActor = Data.EffectSpec.GetContext().GetInstigator(); // 공격자 정보 가져오기

			AMyPlayer* Player = Cast<AMyPlayer>(InstigatorActor);

			if (Player)
			{
				AMonster* Monster = Cast<AMonster>(TargetActor);

				if (Monster->bIsCriticaled)
				{
					float PlayerCritDamage = Cast<ULostArkPlayerAttributeSet>(Player->GetAbilitySystemComponent()->GetAttributeSet(ULostArkPlayerAttributeSet::StaticClass()))->GetCritDamage();
					SetDamage(GetDamage() * PlayerCritDamage);
				}

				SetMonsterCurrentLifePoint(FMath::Clamp(GetMonsterCurrentLifePoint() - GetDamage(), MinimumHealth, GetMonsterMaxLifePoint()));
				OnGetDamage.Broadcast(InstigatorActor, GetDamage());

				Monster->SetDamageWidgetColor();
			}
		}

		SetDamage(0.0f);
	}

	if (bIsSet && (GetMonsterCurrentLifePoint() <= 0.0f) && !bOutOfHealth)
	{
		Data.Target.AddLooseGameplayTag(LOSTARKTAG_CHARACTER_ISDEAD);
		OnOutOfHealth.Broadcast();
	}

	bOutOfHealth = (GetMonsterCurrentLifePoint() <= 0.0f);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}

void ULostArkMonsterAttributeSet::OnRep_EXP(const FGameplayAttributeData& OldEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, EXP, OldEXP);
}

void ULostArkMonsterAttributeSet::OnRep_MonsterMaxLifePoint(const FGameplayAttributeData& OldMonsterMaxLifePoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, MonsterMaxLifePoint, OldMonsterMaxLifePoint);
}

void ULostArkMonsterAttributeSet::OnRep_ATK(const FGameplayAttributeData& OldATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, ATK, OldATK);
}

void ULostArkMonsterAttributeSet::OnRep_MaxATK(const FGameplayAttributeData& OldMaxATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, MaxATK, OldMaxATK);
}

void ULostArkMonsterAttributeSet::OnRep_DEF(const FGameplayAttributeData& OldDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, DEF, OldDEF);
}

void ULostArkMonsterAttributeSet::OnRep_MonsterCurrentLifePoint(const FGameplayAttributeData& OldMonsterCurrentLifePoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, MonsterCurrentLifePoint, OldMonsterCurrentLifePoint);
}

void ULostArkMonsterAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkMonsterAttributeSet, Damage, OldDamage);
}
