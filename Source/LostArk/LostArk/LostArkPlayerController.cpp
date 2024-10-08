// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArkPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"
#include "../Monster/NamedMonster.h"
#include "Engine/World.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/OverlayWidget.h"
#include "../Player/LostArkPlayerState.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../AbilitySystem/LostArkMonsterAttributeSet.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../ChaosDungeon/ChaosDungeonMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

int32 ALostArkPlayerController::MonsterWidgetCount = 0;

int32 ALostArkPlayerController::NamedWidgetCount = 0;

ALostArkPlayerController::ALostArkPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	PrimaryActorTick.bCanEverTick = true;
	FollowTime = 0.f;
}



void ALostArkPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	GetWorldTimerManager().SetTimer(LineTraceTimerHandle, this, &ALostArkPlayerController::CheckMouseOver, 0.1f, true);
}

void ALostArkPlayerController::CheckMouseOver()
{
	//deprojectmousepositiontoworld, linetrace로 관성 추적해서
	//캐릭터 충돌 하면
	//이름 띄우게
	//DeprojectMousePositionToWorld(FVector& WorldLocation, FVector& WorldDirection)
	//LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//캐릭터의 주위에 Sphere Collision? 틱 0.1초 or linetrace 0.1초 단위
	if (AChaosDungeonMode* GameMode = GetWorld()->GetAuthGameMode<AChaosDungeonMode>())
	{
		FVector WorldLocation, WorldDirection;

		if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			FVector Start = WorldLocation;
			FVector End = WorldLocation + (WorldDirection * 10000.f);

			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(GetPawn());

			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

			if (bHit)
			{
				AActor* HitActor = HitResult.GetActor();
				APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
				if (PlayerHUD)
				{
					if (HitActor)
					{

						if (HitActor->IsA(NamedClass))
						{
							ANamedMonster* NamedMonster = Cast<ANamedMonster>(HitActor);
							if (NamedMonster)
							{
								HandleHUDNamedMonster(PlayerHUD, NamedMonster);
								UpdateHealth(NamedMonster);
							}
						}
						if (HitActor->IsA(MonsterClass))
						{
							AMonster* Monster = Cast<AMonster>(HitActor);
							if (Monster)
							{
								HandleHUDCommonMonster(PlayerHUD, Monster);
								UpdateHealth(Monster);
							}
						}
					}
				}
			}
		}
	}
}

void ALostArkPlayerController::HandleHUDCommonMonster(APlayerHUD* PlayerHUD, AMonster* Monster)
{
	if (PlayerHUD->OverlayWidget->CommonHPClass)
	{
		if (PlayerHUD->OverlayWidget->WBPHPBoss)
		{
			if (PlayerHUD->OverlayWidget->WBPHPBoss->GetVisibility() == ESlateVisibility::Visible)
			{
				if (PlayerHUD->OverlayWidget->WBPHPCommon)
				{
					PlayerHUD->OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Collapsed);
				}
			}
			else if (!PlayerHUD->OverlayWidget->WBPHPBoss->bIsCreated || (PlayerHUD->OverlayWidget->WBPHPBoss->bIsCreated && !PlayerHUD->OverlayWidget->WBPHPBoss->bIsAlive))
			{
				if (PlayerHUD->OverlayWidget->WBPHPCommon)
				{
					if (PlayerHUD->OverlayWidget->WBPHPNamed && PlayerHUD->OverlayWidget->WBPHPNamed->GetVisibility() != ESlateVisibility::Collapsed)
					{
						PlayerHUD->OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Collapsed);
					}
					if (PlayerHUD->OverlayWidget->WBPHPCommon && PlayerHUD->OverlayWidget->WBPHPCommon->GetVisibility() == ESlateVisibility::Collapsed)
					{
						PlayerHUD->OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
		}
	}
}

void ALostArkPlayerController::HandleHUDNamedMonster(APlayerHUD* PlayerHUD, ANamedMonster* NamedMonster)
{
	if (PlayerHUD && PlayerHUD->OverlayWidget->NamedHPClass)
	{
		if (PlayerHUD->OverlayWidget->WBPHPBoss)
		{
			if (PlayerHUD->OverlayWidget->WBPHPBoss->GetVisibility() == ESlateVisibility::Visible)
			{
				if (PlayerHUD->OverlayWidget->WBPHPNamed)
				{
					PlayerHUD->OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Collapsed);
				}
			}
			else if (!PlayerHUD->OverlayWidget->WBPHPBoss->bIsCreated || (PlayerHUD->OverlayWidget->WBPHPBoss->bIsCreated && !PlayerHUD->OverlayWidget->WBPHPBoss->bIsAlive))
			{
				if (PlayerHUD->OverlayWidget->WBPHPNamed)
				{
					if (PlayerHUD->OverlayWidget->WBPHPCommon && PlayerHUD->OverlayWidget->WBPHPCommon->GetVisibility() != ESlateVisibility::Collapsed)
					{
						PlayerHUD->OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Collapsed);
					}
					if (PlayerHUD->OverlayWidget->WBPHPNamed && PlayerHUD->OverlayWidget->WBPHPNamed->GetVisibility() == ESlateVisibility::Collapsed)
					{
						PlayerHUD->OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
		}
	}
}

void ALostArkPlayerController::UpdateHealth(AMonster* Monster)
{
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(GetHUD());
	if (PlayerHUD)
	{
		ULostArkMonsterAttributeSet* MonsterAttributeSet = Cast<ULostArkMonsterAttributeSet>(Monster->GetAttributeSet());
		if (PlayerHUD->OverlayWidget)
		{
			switch (Monster->MonsterType)
			{
			case EMonsterType::Named:
				if (PlayerHUD->OverlayWidget->WBPHPNamed)
				{
					float CurrentLifePoint = PlayerHUD->OverlayWidget->WBPHPNamed->GetCurrentHP();
					float MaxLifePoint = PlayerHUD->OverlayWidget->WBPHPNamed->GetMaxHP();
					float CurrentMonsterLifePoint = MonsterAttributeSet->GetMonsterCurrentLifePoint();
					float CurrentMonsterMaxLifePoint = MonsterAttributeSet->GetMonsterMaxLifePoint();

					if (CurrentLifePoint != CurrentMonsterLifePoint)
					{
						PlayerHUD->OverlayWidget->WBPHPNamed->SetCurrentHP(round(CurrentMonsterLifePoint));
						PlayerHUD->OverlayWidget->WBPHPNamed->SetHPBarPercent(CurrentMonsterLifePoint, CurrentMonsterMaxLifePoint);
					}
					if (MaxLifePoint != CurrentMonsterMaxLifePoint)
					{
						PlayerHUD->OverlayWidget->WBPHPNamed->SetMaxHP(round(CurrentMonsterMaxLifePoint));
						PlayerHUD->OverlayWidget->WBPHPNamed->SetHPBarPercent(CurrentMonsterLifePoint, CurrentMonsterMaxLifePoint);
					}
				}
				break;
			case EMonsterType::Common:
				if (PlayerHUD->OverlayWidget->WBPHPCommon)
				{
					float CurrentLifePoint = PlayerHUD->OverlayWidget->WBPHPCommon->GetCurrentHP();
					float MaxLifePoint = PlayerHUD->OverlayWidget->WBPHPCommon->GetMaxHP();
					float CurrentMonsterLifePoint = MonsterAttributeSet->GetMonsterCurrentLifePoint();
					float CurrentMonsterMaxLifePoint = MonsterAttributeSet->GetMonsterMaxLifePoint();

					if (CurrentLifePoint != CurrentMonsterLifePoint)
					{
						PlayerHUD->OverlayWidget->WBPHPCommon->SetCurrentHP(round(CurrentMonsterLifePoint));
						PlayerHUD->OverlayWidget->WBPHPCommon->SetHPBarPercent(CurrentMonsterLifePoint, CurrentMonsterMaxLifePoint);
					}
					if (MaxLifePoint != CurrentMonsterMaxLifePoint)
					{
						PlayerHUD->OverlayWidget->WBPHPCommon->SetMaxHP(round(CurrentMonsterMaxLifePoint));
						PlayerHUD->OverlayWidget->WBPHPCommon->SetHPBarPercent(CurrentMonsterLifePoint, CurrentMonsterMaxLifePoint);
					}
				}
				break;
			}
		}
	}
}

void ALostArkPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ALostArkPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ALostArkPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ALostArkPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ALostArkPlayerController::OnSetDestinationReleased);
		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ALostArkPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ALostArkPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ALostArkPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ALostArkPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ALostArkPlayerController::InteractionStarted);

		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ALostArkPlayerController::TestTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALostArkPlayerController::SetupGASInputComponent()
{
	ALostArkPlayerState* PS = GetPlayerState<ALostArkPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ALostArkPlayerController::GASInputPressed, 0);
	}

}

void ALostArkPlayerController::GASInputPressed(int32 InputId)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(GetPawn());
	ALostArkPlayerState* PS = Cast<ALostArkPlayerState>(MyPlayer->GetPlayerState());
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void ALostArkPlayerController::GASInputReleased(int32 InputId)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(GetPawn());
	ALostArkPlayerState* PS = Cast<ALostArkPlayerState>(MyPlayer->GetPlayerState());
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}

void ALostArkPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ALostArkPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);
	if (ControlledPawn != nullptr)
	{
		if (MyPlayer->CurrentState == ECharacterState::Idle || MyPlayer->CurrentState == ECharacterState::Battle || MyPlayer->CurrentState == ECharacterState::Combat)
		{
			/*MyPlayer->SetPlayerState(ECharacterState::Moving);*/
			FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		}
	}
}

void ALostArkPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ALostArkPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ALostArkPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ALostArkPlayerController::InteractionStarted()
{
	APawn* ControlledPawn = GetPawn();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);

	MyPlayer->bIsInteractioned = true;
}

void ALostArkPlayerController::TestTriggered()
{
	APawn* ControlledPawn = GetPawn();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);

	const UAttributeSet* AttributeSet = MyPlayer->GetAbilitySystemComponent()->GetAttributeSet(ULostArkPlayerAttributeSet::StaticClass());
	const ULostArkPlayerAttributeSet* PlayerAttributeSet = Cast< ULostArkPlayerAttributeSet>(AttributeSet);

	UE_LOG(LogTemp, Warning, TEXT("%f"), PlayerAttributeSet->GetEXP());
}
