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

	static ConstructorHelpers::FClassFinder<AMonster> MonsterBlueprint(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Monster/BP_Common'"));
	if (MonsterBlueprint.Class)
	{
		MonsterClass = MonsterBlueprint.Class;
	}

	static ConstructorHelpers::FClassFinder<ANamedMonster> NamedBlueprint(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Monster/BP_Named'"));
	if (NamedBlueprint.Class)
	{
		NamedClass = NamedBlueprint.Class;
	}
}



void ATP_TopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

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
	if (PlayerHUD->CommonHPClass)
	{
		if (PlayerHUD->BossHP)
		{
			if (PlayerHUD->BossHP->bIsCreated && PlayerHUD->BossHP->bIsAlive)
			{
				if (PlayerHUD->CommonHP)
				{
					PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else if (!PlayerHUD->BossHP->bIsCreated || (PlayerHUD->BossHP->bIsCreated && !PlayerHUD->BossHP->bIsAlive))
			{
				if (PlayerHUD->CommonHP)
				{
					if (PlayerHUD->NamedHP && PlayerHUD->NamedHP->GetVisibility() != ESlateVisibility::Hidden)
					{
						PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Hidden);
					}
					if (PlayerHUD->CommonHP && PlayerHUD->CommonHP->GetVisibility() == ESlateVisibility::Hidden)
					{
						PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Visible);
					}
					if (MonsterWidgetCount == 0)
					{
						PlayerHUD->CommonHP = CreateWidget<UMonsterCommonHPWidget>(this, PlayerHUD->CommonHPClass);
						if (PlayerHUD->CommonHP)
						{
							PlayerHUD->CommonHP->AddToViewport();
							PlayerHUD->CommonHP->UpdateHPBar(Monster->Stat.CurrentLifePoint, Monster->Stat.MaxLifePoint);
							PlayerHUD->CommonHP->UpdateName(Monster->Name);
						}
					}
					else
					{
						if (PlayerHUD->CommonHP)
						{
							if (PlayerHUD->CommonHP->GetCurrentHP() != Monster->Stat.CurrentLifePoint || PlayerHUD->CommonHP->GetMaxHP() != Monster->Stat.MaxLifePoint)
							{
								PlayerHUD->CommonHP->UpdateHPBar(Monster->Stat.CurrentLifePoint, Monster->Stat.MaxLifePoint);

								if (PlayerHUD->CommonHP->GetCurrentHP() < 0.0f)
								{
									PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Hidden);
								}

								else
								{
									PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Visible);
								}
							}
							if (PlayerHUD->CommonHP->GetName() != Monster->Name)
							{
								PlayerHUD->CommonHP->UpdateName(Monster->Name);
							}
						}
					}
					++MonsterWidgetCount;
				}
			}
		}
	}
}

void ATP_TopDownPlayerController::HandleHUDNamedMonster(APlayerHUD* PlayerHUD, ANamedMonster* NamedMonster)
{
	if (PlayerHUD && PlayerHUD->NamedHPClass)
	{
		if (PlayerHUD->BossHP)
		{
			if (PlayerHUD->BossHP->bIsCreated && PlayerHUD->BossHP->bIsAlive)
			{
				if (PlayerHUD->NamedHP)
				{
					PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else if (!PlayerHUD->BossHP->bIsCreated || (PlayerHUD->BossHP->bIsCreated && !PlayerHUD->BossHP->bIsAlive))
			{
				if (PlayerHUD->NamedHP)
				{
					if (PlayerHUD->CommonHP && PlayerHUD->CommonHP->GetVisibility() != ESlateVisibility::Hidden)
					{
						PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Hidden);
					}
					if (PlayerHUD->NamedHP && PlayerHUD->NamedHP->GetVisibility() == ESlateVisibility::Hidden)
					{
						PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Visible);
					}
					if (NamedWidgetCount == 0)
					{
						PlayerHUD->NamedHP = CreateWidget<UMonsterNamedHPWidget>(this, PlayerHUD->NamedHPClass);

						if (PlayerHUD->NamedHP)
						{
							PlayerHUD->NamedHP->AddToViewport();
							PlayerHUD->NamedHP->UpdateHPBar(NamedMonster->Stat.CurrentLifePoint, NamedMonster->Stat.MaxLifePoint);
							PlayerHUD->NamedHP->UpdateName(NamedMonster->Name);
						}
					}
					else
					{
						if (PlayerHUD->NamedHP)
						{
							if (PlayerHUD->NamedHP->GetCurrentHP() != NamedMonster->Stat.CurrentLifePoint || PlayerHUD->NamedHP->GetMaxHP() != NamedMonster->Stat.MaxLifePoint)
							{
								PlayerHUD->NamedHP->UpdateHPBar(NamedMonster->Stat.CurrentLifePoint, NamedMonster->Stat.MaxLifePoint);

								if (PlayerHUD->NamedHP->GetCurrentHP() < 0.0f)
								{
									PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Hidden);
								}

								else
								{
									PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Visible);
								}
							}

							if (PlayerHUD->NamedHP->GetName() != NamedMonster->Name)
							{
								PlayerHUD->NamedHP->UpdateName(NamedMonster->Name);
							}
						}
					}
					++NamedWidgetCount;
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

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::AttackTriggered);

		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::InteractionTriggered);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
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
		if (MyPlayer->CurrentState == ECharacterState::Idle || MyPlayer->CurrentState == ECharacterState::Battle)
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

void ATP_TopDownPlayerController::AttackTriggered()
{
	APawn* ControlledPawn = GetPawn();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(ControlledPawn);
	if (MyPlayer)
	{
		MyPlayer->Attack();
	}
}

void ATP_TopDownPlayerController::InteractionTriggered()
{

}
