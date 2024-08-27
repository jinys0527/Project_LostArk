// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkPlayerState.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "PlayerHUD.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"

ALostArkPlayerState::ALostArkPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<ULostArkAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULostArkPlayerAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void ALostArkPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostArkPlayerState, Level);
	DOREPLIFETIME(ALostArkPlayerState, ExpeditionLevel);
}

UAbilitySystemComponent* ALostArkPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALostArkPlayerState::OnRep_Level()
{
	//이팩트 + 문구
	//사운드
	UE_LOG(LogTemp, Warning, TEXT("1"));
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetPawn()->GetController());
	if (PC)
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
		if (PlayerHUD)
		{
			if (PlayerHUD->OverlayWidget)
			{
				if (PlayerHUD->OverlayWidget->WBPExpBattle && PlayerHUD->OverlayWidget->WBPExpExpedition)
				{
					PlayerHUD->OverlayWidget->WBPExpBattle->UpdateBattleLevel(GetPlayerLevel());
					PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateBattleLevel(GetPlayerLevel());
				}
			}
		}
	}
}

void ALostArkPlayerState::OnRep_ExpeditionLevel()
{
	//이팩트 + 문구
	//사운드
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetPawn()->GetController());
	if (PC)
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
		if (PlayerHUD)
		{
			if (PlayerHUD->OverlayWidget)
			{
				if (PlayerHUD->OverlayWidget->WBPExpBattle && PlayerHUD->OverlayWidget->WBPExpExpedition)
				{
					PlayerHUD->OverlayWidget->WBPExpBattle->UpdateExpeditionLevel(GetPlayerExpeditionLevel());
					PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateExpeditionLevel(GetPlayerExpeditionLevel());
				}
			}
		}
	}
}
