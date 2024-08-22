// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EffectProperties.h"
#include "LostArkPlayerAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerOutOfHealthDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerGetDamageDelegate, AActor*, DamageCauser, float, Damage);


/**
 * 
 */
UCLASS()
class LOSTARK_API ULostArkPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ULostArkPlayerAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	mutable FPlayerOutOfHealthDelegate OnOutOfHealth;
	mutable FPlayerGetDamageDelegate OnGetDamage;

	bool bOutOfHealth = false;

	/*
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HP, Category = "Primary Attributes")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, HP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponATK, Category = "Primary Attributes")
	FGameplayAttributeData WeaponATK;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, WeaponATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Ability, Category = "Primary Attributes")
	FGameplayAttributeData Ability;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Ability);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorDEF, Category = "Primary Attributes")
	FGameplayAttributeData ArmorDEF;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, ArmorDEF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageIncrease, Category = "Primary Attributes")
	FGameplayAttributeData DamageIncrease;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, DamageIncrease);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EXP, Category = "Primary Attributes")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, EXP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Crit, Category = "Primary Attributes")
	FGameplayAttributeData Crit;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Crit);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Specialization, Category = "Primary Attributes")
	FGameplayAttributeData Specialization;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Specialization);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Domination, Category = "Primary Attributes")
	FGameplayAttributeData Domination;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Domination);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Swiftness, Category = "Primary Attributes")
	FGameplayAttributeData Swiftness;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Swiftness);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Endurance, Category = "Primary Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Endurance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Expertise, Category = "Primary Attributes")
	FGameplayAttributeData Expertise;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Expertise);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData HitRate;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, HitRate);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Dodge;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Dodge);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDamage, Category = "Primary Attributes")
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, CritDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RequiredEXP, Category = "Primary Attributes")
	FGameplayAttributeData RequiredEXP;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, RequiredEXP);

	/*
	 * Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxLifePoint, Category = "Secondary Attributes")
	FGameplayAttributeData MaxLifePoint;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MaxLifePoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxManaPoint, Category = "Secondary Attributes")
	FGameplayAttributeData MaxManaPoint;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MaxManaPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DebuffTimeBonus, Category = "Secondary Attributes")
	FGameplayAttributeData DebuffTimeBonus;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, DebuffTimeBonus);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaggerDamage, Category = "Secondary Attributes")
	FGameplayAttributeData StaggerDamage;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, StaggerDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAP, Category = "Secondary Attributes")
	FGameplayAttributeData MaxAP;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MaxAP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ATK, Category = "Secondary Attributes")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, ATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxATK, Category = "Secondary Attributes")
	FGameplayAttributeData MaxATK;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MaxATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhyDEF, Category = "Secondary Attributes")
	FGameplayAttributeData PhyDEF;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, PhyDEF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagDEF, Category = "Secondary Attributes")
	FGameplayAttributeData MagDEF;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MagDEF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Block, Category = "Secondary Attributes")
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Block);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritRate, Category = "Secondary Attributes")
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, CritRate);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageIncreaseOnIncapacitated, Category = "Secondary Attributes")
	FGameplayAttributeData DamageIncreaseOnIncapacitated;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, DamageIncreaseOnIncapacitated);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HPRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HPRegeneration;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, HPRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MPRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData MPRegeneration;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, MPRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SkillCooldownDecrease, Category = "Secondary Attributes")
	FGameplayAttributeData SkillCooldownDecrease;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, SkillCooldownDecrease);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IncreaseNormalSkillDamage, Category = "Secondary Attributes")
	FGameplayAttributeData IncreaseNormalSkillDamage;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, IncreaseNormalSkillDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FuryMeterGain, Category = "Secondary Attributes")
	FGameplayAttributeData FuryMeterGain;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, FuryMeterGain);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BloodRushDamage, Category = "Secondary Attributes")
	FGameplayAttributeData BloodRushDamage;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, BloodRushDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DebuffTimeReduction, Category = "Secondary Attributes")
	FGameplayAttributeData DebuffTimeReduction;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, DebuffTimeReduction);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Secondary Attributes")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Shield);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Healing, Category = "Secondary Attributes")
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Healing);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RageTimeBonus, Category = "Secondary Attributes")
	FGameplayAttributeData RageTimeBonus;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, RageTimeBonus);

	/*
	 * Vital Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentLifePoint, Category = "Vital Attributes")
	FGameplayAttributeData CurrentLifePoint;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, CurrentLifePoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentManaPoint, Category = "Vital Attributes")
	FGameplayAttributeData CurrentManaPoint;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, CurrentManaPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AP, Category = "Vital Attributes")
	FGameplayAttributeData AP;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, AP);

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(ULostArkPlayerAttributeSet, Damage);

	/*
	 * Primary Attribute Functions
	 */

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldHP) const;

	UFUNCTION()
	void OnRep_WeaponATK(const FGameplayAttributeData& OldWeaponATK) const;

	UFUNCTION()
	void OnRep_Ability(const FGameplayAttributeData& OldAbility) const;

	UFUNCTION()
	void OnRep_ArmorDEF(const FGameplayAttributeData& OldArmorDEF) const;

	UFUNCTION()
	void OnRep_DamageIncrease(const FGameplayAttributeData& OldDamageIncrease) const;

	UFUNCTION()
	void OnRep_EXP(const FGameplayAttributeData& OldEXP) const;

	UFUNCTION()
	void OnRep_Crit(const FGameplayAttributeData& OldCrit) const;

	UFUNCTION()
	void OnRep_Specialization(const FGameplayAttributeData& OldSpecialization) const;

	UFUNCTION()
	void OnRep_Domination(const FGameplayAttributeData& OldDomination) const;

	UFUNCTION()
	void OnRep_Swiftness(const FGameplayAttributeData& OldSwiftness) const;

	UFUNCTION()
	void OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const;

	UFUNCTION()
	void OnRep_Expertise(const FGameplayAttributeData& OldExpertise) const;

	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;

	UFUNCTION()
	void OnRep_RequiredEXP(const FGameplayAttributeData& OldRequiredEXP) const;

	 /*
	  * Secondary Attribute Functions
	  */

	UFUNCTION()
	void OnRep_MaxLifePoint(const FGameplayAttributeData& OldMaxLifePoint) const;

	UFUNCTION()
	void OnRep_MaxManaPoint(const FGameplayAttributeData& OldMaxManaPoint) const;

	UFUNCTION()
	void OnRep_DebuffTimeBonus(const FGameplayAttributeData& OldDebuffTimeBonus) const;

	UFUNCTION()
	void OnRep_RageTimeBonus(const FGameplayAttributeData& OldRageTimeBonus) const;

	UFUNCTION()
	void OnRep_StaggerDamage(const FGameplayAttributeData& OldStaggerDamage) const;

	UFUNCTION()
	void OnRep_MaxAP(const FGameplayAttributeData& OldMaxAP) const;

	UFUNCTION()
	void OnRep_ATK(const FGameplayAttributeData& OldATK) const;
	
	UFUNCTION()
	void OnRep_MaxATK(const FGameplayAttributeData& OldMaxATK) const;

	UFUNCTION()
	void OnRep_PhyDEF(const FGameplayAttributeData& OldPhyDEF) const;

	UFUNCTION()
	void OnRep_MagDEF(const FGameplayAttributeData& OldMagDEF) const;

	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData& OldBlock) const;

	UFUNCTION()
	void OnRep_CritRate(const FGameplayAttributeData& OldCritRate) const;

	UFUNCTION()
	void OnRep_DamageIncreaseOnIncapacitated(const FGameplayAttributeData& OldDamageIncreaseOnIncapacitated) const;

	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

	UFUNCTION()
	void OnRep_HPRegeneration(const FGameplayAttributeData& OldHPRegeneration) const;

	UFUNCTION()
	void OnRep_MPRegeneration(const FGameplayAttributeData& OldMPRegeneration) const;

	UFUNCTION()
	void OnRep_SkillCooldownDecrease(const FGameplayAttributeData& OldSkillCooldownDecrease) const;

	UFUNCTION()
	void OnRep_IncreaseNormalSkillDamage(const FGameplayAttributeData& OldIncreaseNormalSkillDamage) const;

	UFUNCTION()
	void OnRep_FuryMeterGain(const FGameplayAttributeData& OldFuryMeterGain) const;

	UFUNCTION()
	void OnRep_BloodRushDamage(const FGameplayAttributeData& OldBloodRushDamage) const;

	UFUNCTION()
	void OnRep_DebuffTimeReduction(const FGameplayAttributeData& OldDebuffTimeReduction) const;

	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& OldDebuffTimeReduction) const;

	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& OldDebuffTimeReduction) const;

	  /*
	   * Vital Attribute Functions
	   */
	
	UFUNCTION()
	void OnRep_CurrentLifePoint(const FGameplayAttributeData& OldLCurrentLifePoint) const;

	UFUNCTION()
	void OnRep_CurrentManaPoint(const FGameplayAttributeData& OldCurrentManaPoint) const;

	UFUNCTION()
	void OnRep_AP(const FGameplayAttributeData& OldAP) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
