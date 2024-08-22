// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownPlayerController.h"
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
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

int32 ATP_TopDownPlayerController::MonsterWidgetCount = 0;

int32 ATP_TopDownPlayerController::NamedWidgetCount = 0;

ATP_TopDownPlayerController::ATP_TopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	PrimaryActorTick.bCanEverTick = true;
	FollowTime = 0.f;
}



void ATP_TopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	GetWorldTimerManager().SetTimer(LineTraceTimerHandle, this, &ATP_TopDownPlayerController::CheckMouseOver, 0.1f, true);
}

void ATP_TopDownPlayerController::CheckMouseOver()
{
	//deprojectmousepositiontoworld, linetrace로 관성 추적해서
	//캐릭터 충돌 하면
	//이름 띄우게
	//DeprojectMousePositionToWorld(FVector& WorldLocation, FVector& WorldDirection)
	//LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//캐릭터의 주위에 Sphere Collision? 틱 0.1초 or linetrace 0.1초 단위
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
						}
					}

					else if (HitActor->IsA(MonsterClass))
					{
						AMonster* Monster = Cast<AMonster>(HitActor);
						if (Monster)
						{
							HandleHUDCommonMonster(PlayerHUD, Monster);
						}
					}
				}
			}
		}
	}
}

void ATP_TopDownPlayerController::HandleHUDCommonMonster(APlayerHUD* PlayerHUD, AMonster* Monster)
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

void ATP_TopDownPlayerController::HandleHUDNamedMonster(APlayerHUD* PlayerHUD, ANamedMonster* NamedMonster)
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

void ATP_TopDownPlayerController::SetupInputComponent()
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
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATP_TopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATP_TopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATP_TopDownPlayerController::OnSetDestinationReleased);
		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATP_TopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATP_TopDownPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATP_TopDownPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::InteractionTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATP_TopDownPlayerController::SetupGASInputComponent()
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(GetPawn());
	ALostArkPlayerState* PS = Cast<ALostArkPlayerState>(MyPlayer->GetPlayerState());
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::GASInputPressed, 0);
	}
	
}

void ATP_TopDownPlayerController::GASInputPressed(int32 InputId)
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

void ATP_TopDownPlayerController::GASInputReleased(int32 InputId)
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

void ATP_TopDownPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATP_TopDownPlayerController::OnSetDestinationTriggered()
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

void ATP_TopDownPlayerController::OnSetDestinationReleased()
{
	APawn* ControlledPawn = GetPawn();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);
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
void ATP_TopDownPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATP_TopDownPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

//void ATP_TopDownPlayerController::AttackTriggered()
//{
//	APawn* ControlledPawn = GetPawn();
//	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);
//	if (MyPlayer)
//	{
//		MyPlayer->Attack();
//	}
//}

void ATP_TopDownPlayerController::InteractionTriggered()
{

}
