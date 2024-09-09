// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LostArk/Tag/LostArkGameplayTag.h"
#include "../Player/MyPlayer.h"


ULostArkPlayerAttributeSet::ULostArkPlayerAttributeSet()
{
	//특성
	InitCrit(10.0f);
	InitSpecialization(10.0f);
	InitSwiftness(10.0f);
	InitDomination(10.0f);
	InitEndurance(10.0f);
	InitExpertise(10.0f);

	InitRequiredEXP(10.0f);
	InitExpeditionRequiredEXP(10.0f);

	InitWeaponATK(69.0f);
	InitAbility(206.0f);
	InitAP(0.f);
	InitMaxAP(0.f);
	InitArmorDEF(140.909090f);

	InitCritDamage(2.0f);
	InitDamageIncrease(0.f);
	InitDodge(0.f);

	InitEXP(0.f);
	InitHitRate(1.0f);
}

void ULostArkPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*
	 * Primary Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, WeaponATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Ability, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, ArmorDEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, DamageIncrease, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, EXP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Crit, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Specialization, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Domination, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Swiftness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Expertise, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, RequiredEXP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, ExpeditionEXP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, ExpeditionRequiredEXP, COND_None, REPNOTIFY_Always);

	/*
	 * Secondary Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MaxLifePoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MaxManaPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, DebuffTimeBonus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, StaggerDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MaxAP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, ATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MaxATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, PhyDEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MagDEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Block, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, DamageIncreaseOnIncapacitated, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, HPRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, MPRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, SkillCooldownDecrease, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, IncreaseNormalSkillDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, FuryMeterGain, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, BloodRushDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, DebuffTimeReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, Healing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, RageTimeBonus, COND_None, REPNOTIFY_Always);

	/*
	 * Vital Attributes
	 */

	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, CurrentLifePoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, CurrentManaPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULostArkPlayerAttributeSet, AP, COND_None, REPNOTIFY_Always);
}

void ULostArkPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void ULostArkPlayerAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
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

void ULostArkPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;
	if (Data.EvaluatedData.Attribute == GetCurrentLifePointAttribute())
	{
		SetCurrentLifePoint(FMath::Clamp(GetCurrentLifePoint(), MinimumHealth, GetMaxLifePoint()));
	}
	if (Data.EvaluatedData.Attribute == GetCurrentManaPointAttribute())
	{
		SetCurrentManaPoint(FMath::Clamp(GetCurrentManaPoint(), 0.f, GetMaxManaPoint()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetCurrentLifePoint(FMath::Clamp(GetCurrentLifePoint() - GetDamage(), MinimumHealth, GetMaxLifePoint()));

		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AActor* InstigatorActor = nullptr;

		if (Data.EffectSpec.GetContext().GetInstigator())
		{
			InstigatorActor = Data.EffectSpec.GetContext().GetInstigator(); // 공격자 정보 가져오기
		}

		OnGetDamage.Broadcast(InstigatorActor, GetDamage());

		SetDamage(0.0f);
	}
	if (Data.EvaluatedData.Attribute == GetEXPAttribute())
	{
		float CurrentEXP = GetEXP();
		float CurrentRequiredEXP = GetRequiredEXP();
		float OverEXP = CurrentEXP - CurrentRequiredEXP;
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AMyPlayer* MyPlayer = Cast<AMyPlayer>(TargetActor);
		while (OverEXP >= 0)
		{
			MyPlayer->LevelUP();
			SetEXP(OverEXP);
			CurrentRequiredEXP = GetRequiredEXP();
			OverEXP = GetEXP() - CurrentRequiredEXP;
			
		}	
	}
	if (Data.EvaluatedData.Attribute == GetExpeditionEXPAttribute())
	{
		float CurrentEXP = GetExpeditionEXP();
		float CurrentRequiredEXP = GetExpeditionRequiredEXP();
		float OverEXP = CurrentEXP - CurrentRequiredEXP;

		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AMyPlayer* MyPlayer = Cast<AMyPlayer>(TargetActor);

		while (OverEXP >= 0)
		{
			MyPlayer->ExpeditionLevelUP();
			SetEXP(OverEXP);
			CurrentRequiredEXP = GetExpeditionRequiredEXP();
			OverEXP = GetExpeditionEXP() - CurrentRequiredEXP;
		}
	}

	if ((GetCurrentLifePoint() <= 0.0f) && !bOutOfHealth)
	{
		Data.Target.AddLooseGameplayTag(LOSTARKTAG_CHARACTER_ISDEAD);
		OnOutOfHealth.Broadcast();
	}

	bOutOfHealth = (GetCurrentLifePoint() <= 0.0f);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}

/*
 * Primary Attribute Functions
 */

void ULostArkPlayerAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, HP, OldHP);
}

void ULostArkPlayerAttributeSet::OnRep_WeaponATK(const FGameplayAttributeData& OldWeaponATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, WeaponATK, OldWeaponATK);
}

void ULostArkPlayerAttributeSet::OnRep_Ability(const FGameplayAttributeData& OldAbility) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Ability, OldAbility);
}

void ULostArkPlayerAttributeSet::OnRep_ArmorDEF(const FGameplayAttributeData& OldArmorDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, ArmorDEF, OldArmorDEF);
}

void ULostArkPlayerAttributeSet::OnRep_DamageIncrease(const FGameplayAttributeData& OldDamageIncrease) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, DamageIncrease, OldDamageIncrease);
}

void ULostArkPlayerAttributeSet::OnRep_EXP(const FGameplayAttributeData& OldEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, EXP, OldEXP);
}

void ULostArkPlayerAttributeSet::OnRep_Crit(const FGameplayAttributeData& OldCrit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Crit, OldCrit);
}

void ULostArkPlayerAttributeSet::OnRep_Specialization(const FGameplayAttributeData& OldSpecialization) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Specialization, OldSpecialization);
}

void ULostArkPlayerAttributeSet::OnRep_Domination(const FGameplayAttributeData& OldDomination) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Domination, OldDomination);
}

void ULostArkPlayerAttributeSet::OnRep_Swiftness(const FGameplayAttributeData& OldSwiftness) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Swiftness, OldSwiftness);
}

void ULostArkPlayerAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Endurance, OldEndurance);
}

void ULostArkPlayerAttributeSet::OnRep_Expertise(const FGameplayAttributeData& OldExpertise) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Expertise, OldExpertise);
}

void ULostArkPlayerAttributeSet::OnRep_DamageIncreaseOnIncapacitated(const FGameplayAttributeData& OldDamageIncreaseOnIncapacitated) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, DamageIncreaseOnIncapacitated, OldDamageIncreaseOnIncapacitated);
}

/*
 * Secondary Attribute Functions
 */

void ULostArkPlayerAttributeSet::OnRep_MaxLifePoint(const FGameplayAttributeData& OldMaxLifePoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MaxLifePoint, OldMaxLifePoint);
}

void ULostArkPlayerAttributeSet::OnRep_MaxManaPoint(const FGameplayAttributeData& OldMaxManaPoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MaxManaPoint, OldMaxManaPoint);
}

void ULostArkPlayerAttributeSet::OnRep_DebuffTimeBonus(const FGameplayAttributeData& OldDebuffTimeBonus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, DebuffTimeBonus, OldDebuffTimeBonus);
}

void ULostArkPlayerAttributeSet::OnRep_RageTimeBonus(const FGameplayAttributeData& OldRageTimeBonus) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, RageTimeBonus, OldRageTimeBonus);
}

void ULostArkPlayerAttributeSet::OnRep_StaggerDamage(const FGameplayAttributeData& OldStaggerDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, StaggerDamage, OldStaggerDamage);
}

void ULostArkPlayerAttributeSet::OnRep_MaxAP(const FGameplayAttributeData& OldMaxAP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MaxAP, OldMaxAP);
}

void ULostArkPlayerAttributeSet::OnRep_ATK(const FGameplayAttributeData& OldATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, ATK, OldATK);
}

void ULostArkPlayerAttributeSet::OnRep_MaxATK(const FGameplayAttributeData& OldMaxATK) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MaxATK, OldMaxATK);
}

void ULostArkPlayerAttributeSet::OnRep_PhyDEF(const FGameplayAttributeData& OldPhyDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, PhyDEF, OldPhyDEF);
}

void ULostArkPlayerAttributeSet::OnRep_MagDEF(const FGameplayAttributeData& OldMagDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MagDEF, OldMagDEF);
}

void ULostArkPlayerAttributeSet::OnRep_Block(const FGameplayAttributeData& OldBlock) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Block, OldBlock);
}

void ULostArkPlayerAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, CritRate, OldCritRate);
}

void ULostArkPlayerAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, CritDamage, OldCritDamage);
}

void ULostArkPlayerAttributeSet::OnRep_RequiredEXP(const FGameplayAttributeData& OldRequiredEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, RequiredEXP, OldRequiredEXP);
}

void ULostArkPlayerAttributeSet::OnRep_ExpeditionEXP(const FGameplayAttributeData& OldExpeditionEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, ExpeditionEXP, OldExpeditionEXP);
}

void ULostArkPlayerAttributeSet::OnRep_ExpeditionRequiredEXP(const FGameplayAttributeData& OldExpeditionRequiredEXP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, ExpeditionRequiredEXP, OldExpeditionRequiredEXP);
}

void ULostArkPlayerAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, AttackSpeed, OldAttackSpeed);
}

void ULostArkPlayerAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MovementSpeed, OldMovementSpeed);
}

void ULostArkPlayerAttributeSet::OnRep_HPRegeneration(const FGameplayAttributeData& OldHPRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, HPRegeneration, OldHPRegeneration);
}

void ULostArkPlayerAttributeSet::OnRep_MPRegeneration(const FGameplayAttributeData& OldMPRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, MPRegeneration, OldMPRegeneration);
}

void ULostArkPlayerAttributeSet::OnRep_SkillCooldownDecrease(const FGameplayAttributeData& OldSkillCooldownDecrease) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, SkillCooldownDecrease, SkillCooldownDecrease);
}

void ULostArkPlayerAttributeSet::OnRep_IncreaseNormalSkillDamage(const FGameplayAttributeData& OldIncreaseNormalSkillDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, IncreaseNormalSkillDamage, OldIncreaseNormalSkillDamage);
}

void ULostArkPlayerAttributeSet::OnRep_FuryMeterGain(const FGameplayAttributeData& OldFuryMeterGain) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, FuryMeterGain, OldFuryMeterGain);
}

void ULostArkPlayerAttributeSet::OnRep_BloodRushDamage(const FGameplayAttributeData& OldBloodRushDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, BloodRushDamage, OldBloodRushDamage);
}

void ULostArkPlayerAttributeSet::OnRep_DebuffTimeReduction(const FGameplayAttributeData& OldDebuffTimeReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, DebuffTimeReduction, OldDebuffTimeReduction);
}

void ULostArkPlayerAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Shield, OldShield);
}

void ULostArkPlayerAttributeSet::OnRep_Healing(const FGameplayAttributeData& OldHealing) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, Healing, OldHealing);
}

/*
 * Vital Attribute Functions
 */

void ULostArkPlayerAttributeSet::OnRep_CurrentLifePoint(const FGameplayAttributeData& OldCurrentLifePoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, CurrentLifePoint, OldCurrentLifePoint);
}


void ULostArkPlayerAttributeSet::OnRep_CurrentManaPoint(const FGameplayAttributeData& OldCurrentManaPoint) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, CurrentManaPoint, OldCurrentManaPoint);
}

void ULostArkPlayerAttributeSet::OnRep_AP(const FGameplayAttributeData& OldAP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULostArkPlayerAttributeSet, AP, OldAP);
}
