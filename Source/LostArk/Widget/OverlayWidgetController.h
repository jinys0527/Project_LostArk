// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkWidgetController.h"
#include "GameplayEffectTypes.h"
#include "LostArkUserWidget.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LOSTARK_API UOverlayWidgetController : public ULostArkWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnCurrentLifePointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxLifePointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnCurrentManaPointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaPointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnEXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnRequiredEXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnExpeditionEXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnExpeditionRequiredEXPChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMonsterCurrentLifePointChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMonsterMaxLifePointChanged;

protected:
	void CurrentLifePointChanged(const FOnAttributeChangeData& Data) const;
	void MaxLifePointChanged(const FOnAttributeChangeData& Data) const;
	void CurrentManaPointChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaPointChanged(const FOnAttributeChangeData& Data) const;
	void EXPChanged(const FOnAttributeChangeData& Data) const;
	void RequiredEXPChanged(const FOnAttributeChangeData& Data) const;
	void ExpeditionEXPChanged(const FOnAttributeChangeData& Data) const;
	void ExpeditionRequiredEXPChanged(const FOnAttributeChangeData& Data) const;
	void MonsterCurrentLifePointChanged(const FOnAttributeChangeData& Data) const;
	void MonsterMaxLifePointChanged(const FOnAttributeChangeData& Data) const;
};
