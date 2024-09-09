// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonPortal.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/MoveWidget.h"
#include "../Player/MyPlayer.h"
#include "ChaosDungeonGameInstance.h"
#include "ChaosDungeonGameState.h"
#include "Components/WidgetComponent.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/ProgressWidget.h"
#include "Components/ProgressBar.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "Components/TextBlock.h"
#include "../Player/LostArkPlayerState.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"

AChaosDungeonPortal::AChaosDungeonPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Portal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	Portal->SetupAttachment(Capsule);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AChaosDungeonPortal::OnOverlapBegin);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &AChaosDungeonPortal::OnOverlapEnd);

	MoveWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MoveWidget"));
	MoveWidget->SetupAttachment(RootComponent);
	MoveWidget->SetDrawAtDesiredSize(true);
	MoveWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	MoveWidget->SetCastShadow(false);

	bIsOn = false;
}

void AChaosDungeonPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappedPlayer = Cast<AMyPlayer>(OtherActor);
	if (!Portal->bHiddenInGame)
	{
		MoveWidget->SetHiddenInGame(false);
	}

	bIsOn = true;

	GetWorld()->GetTimerManager().SetTimer(InteractionCheckTimer, this, &AChaosDungeonPortal::CheckInteraction, 0.1f, true);
}

void AChaosDungeonPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedPlayer = nullptr;
	if (!Portal->bHiddenInGame)
	{
		MoveWidget->SetHiddenInGame(true);
	}

	bIsOn = false;

	GetWorld()->GetTimerManager().ClearTimer(InteractionCheckTimer);
}

void AChaosDungeonPortal::LoadLevel(FName LevelName)
{
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, FLatentActionInfo());
}

void AChaosDungeonPortal::SetVisiblePortal()
{
	if (Portal)
	{
		Portal->SetHiddenInGame(false);
	}
	SetActorEnableCollision(true);
}

void AChaosDungeonPortal::CheckInteraction()
{
	if (OverlappedPlayer->bIsInteractioned && bIsOn)
	{
		AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(UGameplayStatics::GetGameState(GetWorld()));

		UChaosDungeonGameInstance* GameInstance;

		GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			ALostArkPlayerState* PlayerState = Cast<ALostArkPlayerState>(OverlappedPlayer->GetPlayerState());
			ULostArkPlayerAttributeSet* LostArkPlayerAttributeSet = Cast<ULostArkPlayerAttributeSet>(PlayerState->GetAttributeSet());

			ATP_TopDownPlayerController* PlayerController = Cast<ATP_TopDownPlayerController>(OverlappedPlayer->GetController());
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());

			if (PlayerController)
			{
				GameInstance->PlayerBattleLevel = PlayerState->GetPlayerLevel();
				GameInstance->PlayerExpeditionLevel = PlayerState->GetPlayerExpeditionLevel();
			}

			if (PlayerHUD)
			{
				if (PlayerHUD->OverlayWidget)
				{
					if (PlayerHUD->OverlayWidget->WBPProgress)
					{
						GameInstance->ProgressValue = PlayerHUD->OverlayWidget->WBPProgress->ProgressValue->GetText().ToString();
						GameInstance->CurrentProgress = PlayerHUD->OverlayWidget->WBPProgress->ChaosDungeonProgressBar->GetPercent();
					}
					if (PlayerHUD->OverlayWidget->WBPExpBattle)
					{
						GameInstance->PlayerBattleEXPBarPercent = PlayerHUD->OverlayWidget->WBPExpBattle->BattleEXPBar->GetPercent();
					}
					if (PlayerHUD->OverlayWidget->WBPExpExpedition)
					{
						GameInstance->PlayerExpeditionEXPBarPercent = PlayerHUD->OverlayWidget->WBPExpExpedition->ExpeditionEXPBar->GetPercent();
					}
				}
			}
		}
		switch (ChaosDungeonState->CurrentState)
		{
		case EDungeonState::Stage1:
			UGameplayStatics::OpenLevel(GetWorld(), "L_LogHill_Stage2");
			break;

		case EDungeonState::Stage2:
			UGameplayStatics::OpenLevel(GetWorld(), "L_LogHill_Stage3");
			break;
		}
	}
}

// Called when the game starts or when spawned
void AChaosDungeonPortal::BeginPlay()
{
	Super::BeginPlay();
	MoveWidget->SetHiddenInGame(true);
	Capsule->SetHiddenInGame(true);
	Portal->SetHiddenInGame(true);
	SetActorEnableCollision(false);
}

// Called every frame
void AChaosDungeonPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

