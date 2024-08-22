// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EffectProperties.h"
#include "LostArkMonsterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMonsterOutOfHealthDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterGetDamageDelegate, AActor*, DamageCauser, float, Damage);

/**
 * 
 */
UCLASS()
class LOSTARK_API ULostArkMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULostArkMonsterAttributeSet();

	mutable FMonsterOutOfHealthDelegate OnOutOfHealth;
	mutable FMonsterGetDamageDelegate OnGetDamage;

	bool bOutOfHealth = false;

	bool bIsSet = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EXP, Category = "Primary Attributes")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, EXP);

	/*
	 * Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MonsterMaxLifePoint, Category = "Secondary Attributes")
	FGameplayAttributeData MonsterMaxLifePoint;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, MonsterMaxLifePoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ATK, Category = "Secondary Attributes")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, ATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxATK, Category = "Secondary Attributes")
	FGameplayAttributeData MaxATK;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, MaxATK);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DEF, Category = "Secondary Attributes")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, DEF);

	/*
	 * Vital Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MonsterCurrentLifePoint, Category = "Vital Attributes")
	FGameplayAttributeData MonsterCurrentLifePoint;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, MonsterCurrentLifePoint);

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(ULostArkMonsterAttributeSet, Damage);

	/*
	 * Primary Attribute Functions
	 */	
	
	UFUNCTION()
	void OnRep_EXP(const FGameplayAttributeData& OldEXP) const;

	/*
	  * Secondary Attribute Functions
	  */

	UFUNCTION()
	void OnRep_MonsterMaxLifePoint(const FGameplayAttributeData& OldMonsterMaxLifePoint) const;

	UFUNCTION()
	void OnRep_ATK(const FGameplayAttributeData& OldATK) const;

	UFUNCTION()
	void OnRep_MaxATK(const FGameplayAttributeData& OldMaxATK) const;

	UFUNCTION()
	void OnRep_DEF(const FGameplayAttributeData& OldDEF) const;

	/*
	  * Vital Attribute Functions
	  */

	UFUNCTION()
	void OnRep_MonsterCurrentLifePoint(const FGameplayAttributeData& OldMonsterCurrentLifePoint) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
