// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkMonsterAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "../Monster/Monster.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const ULostArkPlayerAttributeSet* LostArkPlayerAttributeSet = CastChecked<ULostArkPlayerAttributeSet>(AttributeSet);

	TArray<AActor*> FoundMonsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundMonsters);

	if (FoundMonsters.Num() > 0)
	{
		AMonster* Monster = Cast<AMonster>(FoundMonsters[0]);
		if (Monster)
		{
			ULostArkMonsterAttributeSet* LostArkMonsterAttributeSet = Cast<ULostArkMonsterAttributeSet>(Monster->GetAttributeSet());
			OnMonsterMaxLifePointChanged.Broadcast(LostArkMonsterAttributeSet->GetMonsterMaxLifePoint());
			OnMonsterCurrentLifePointChanged.Broadcast(LostArkMonsterAttributeSet->GetMonsterCurrentLifePoint());
		}
	}

	OnCurrentLifePointChanged.Broadcast(LostArkPlayerAttributeSet->GetCurrentLifePoint());
	OnMaxLifePointChanged.Broadcast(LostArkPlayerAttributeSet->GetMaxLifePoint());
	OnCurrentManaPointChanged.Broadcast(LostArkPlayerAttributeSet->GetCurrentManaPoint());
	OnMaxManaPointChanged.Broadcast(LostArkPlayerAttributeSet->GetMaxManaPoint());
	OnEXPChanged.Broadcast(LostArkPlayerAttributeSet->GetEXP());
	OnRequiredEXPChanged.Broadcast(LostArkPlayerAttributeSet->GetRequiredEXP());
	OnExpeditionEXPChanged.Broadcast(LostArkPlayerAttributeSet->GetExpeditionEXP());
	OnExpeditionRequiredEXPChanged.Broadcast(LostArkPlayerAttributeSet->GetExpeditionRequiredEXP());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const ULostArkPlayerAttributeSet* LostArkPlayerAttributeSet = CastChecked<ULostArkPlayerAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetCurrentLifePointAttribute()).AddUObject(this, &UOverlayWidgetController::CurrentLifePointChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetMaxLifePointAttribute()).AddUObject(this, &UOverlayWidgetController::MaxLifePointChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetCurrentManaPointAttribute()).AddUObject(this, &UOverlayWidgetController::CurrentManaPointChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetMaxManaPointAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaPointChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetEXPAttribute()).AddUObject(this, &UOverlayWidgetController::EXPChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetRequiredEXPAttribute()).AddUObject(this, &UOverlayWidgetController::RequiredEXPChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetExpeditionEXPAttribute()).AddUObject(this, &UOverlayWidgetController::ExpeditionEXPChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		LostArkPlayerAttributeSet->GetExpeditionRequiredEXPAttribute()).AddUObject(this, &UOverlayWidgetController::ExpeditionRequiredEXPChanged);

}

void UOverlayWidgetController::BindToMonsterEvents(AMonster* Monster)
{
	if (Monster)
	{
		ULostArkMonsterAttributeSet* LostArkMonsterAttributeSet = Cast<ULostArkMonsterAttributeSet>(Monster->GetAttributeSet());
		UAbilitySystemComponent* MonsterAbilitySystemComponent = Monster->GetAbilitySystemComponent();

		if (MonsterAbilitySystemComponent && LostArkMonsterAttributeSet)
		{
			MonsterAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				LostArkMonsterAttributeSet->GetMonsterMaxLifePointAttribute()).AddUObject(this, &UOverlayWidgetController::MonsterMaxLifePointChanged);

			MonsterAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				LostArkMonsterAttributeSet->GetMonsterCurrentLifePointAttribute()).AddUObject(this, &UOverlayWidgetController::MonsterCurrentLifePointChanged);
		}	
	}
}

void UOverlayWidgetController::CurrentLifePointChanged(const FOnAttributeChangeData& Data) const
{
	OnCurrentLifePointChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxLifePointChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxLifePointChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::CurrentManaPointChanged(const FOnAttributeChangeData& Data) const
{
	OnCurrentManaPointChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaPointChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaPointChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::EXPChanged(const FOnAttributeChangeData& Data) const
{
	OnEXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::RequiredEXPChanged(const FOnAttributeChangeData& Data) const
{
	OnRequiredEXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ExpeditionEXPChanged(const FOnAttributeChangeData& Data) const
{
	OnExpeditionEXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ExpeditionRequiredEXPChanged(const FOnAttributeChangeData& Data) const
{
	OnExpeditionRequiredEXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MonsterCurrentLifePointChanged(const FOnAttributeChangeData& Data) const
{
	OnMonsterCurrentLifePointChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MonsterMaxLifePointChanged(const FOnAttributeChangeData& Data) const
{
	OnMonsterMaxLifePointChanged.Broadcast(Data.NewValue);
}
