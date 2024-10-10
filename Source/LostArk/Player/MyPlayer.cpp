// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "../Weapon/GreatSword.h"
#include "../Widget/DamageWidget.h"
#include "Engine/World.h"
#include "PlayerHUD.h"
#include "../LostArk/LostArkPlayerController.h"
#include "../Widget/PlayerStatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Animation/AnimInstance_Player.h"
#include "../Player/LostArkPlayerState.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../Tag/LostArkGameplayTag.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/RevivalWidget.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SceneComponent.h"
#include "../ChaosDungeon/ChaosDungeonGameInstance.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"
#include "Components/ProgressBar.h"


AMyPlayer::AMyPlayer() : ABaseCharacter()
{
	bIsEquipped = false;

	bIsInteractioned = false;

	SetPlayerState(ECharacterState::Idle);

	AnimInstance = Cast<UAnimInstance_Player>(GetMesh()->GetAnimInstance());

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	AttachSword();

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		PlayerAnimInstance = Cast<UAnimInstance_Player>(MeshComp->GetAnimInstance());
	}
}

void AMyPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyPlayer::SetPlayerState(ECharacterState NewState)
{
	CurrentState = NewState;
}

void AMyPlayer::PlayDead()
{
	PlayAnimMontage(DeathMontage, 1.0f);
}

void AMyPlayer::PlayHitReaction()
{
	if (AnimInstance)
	{
		if (CurrentState == ECharacterState::Idle && !AnimInstance->Montage_IsPlaying(EquipSwordMontage))
		{
			PlayAnimMontage(HitReactionMontage, 1.0f);
		}
		else if ((CurrentState == ECharacterState::Battle || CurrentState == ECharacterState::Attacking || CurrentState == ECharacterState::Combat) && !AnimInstance->Montage_IsPlaying(AttackMontage) && !AnimInstance->Montage_IsPlaying(EquipSwordMontage) && !AnimInstance->Montage_IsPlaying(UnEquipSwordMontage))
		{
			PlayAnimMontage(HitReactionBattleMontage, 1.0f);
		}
	}
}

void AMyPlayer::PlayResurrection()
{
	PlayAnimMontage(ResurrectionMontage);
}

void AMyPlayer::SetDead()
{
	Super::SetDead();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
		if (PlayerHUD)
		{
			PlayerHUD->OverlayWidget->WBPRevival->SetVisibility(ESlateVisibility::Visible);
		}
		Tags.Remove(FName("Player"));
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->ClearAllAbilities();
		}
	}
}

void AMyPlayer::OnOutOfHealth()
{
	SetDead();
}

void AMyPlayer::OnGetDamage(AActor* DamageCauser, float Damage)
{
	ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(GetController());
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	if (PlayerHUD)
	{
		if (DamageClass)
		{
			wDamage = CreateWidget<UDamageWidget>(PC, DamageClass);
			if (wDamage)
			{
				wDamage->SynchronizeProperties();
				wDamage->DamageValue->SetColorAndOpacity(FLinearColor(0.708376, 0.028426, 0.013702));
				wDamage->DamageValue->SetShadowOffset(FVector2D(0, 0));
				wDamage->DamageValue->SetShadowColorAndOpacity(FLinearColor::Transparent);

				FVector PlayerLocation = GetActorLocation();
				FVector MonsterLocation = DamageCauser->GetActorLocation();

				FVector DirectionVector = MonsterLocation - PlayerLocation;
				DirectionVector.Normalize();

				float DesiredDistance = 30.0f;
				WidgetLocation = PlayerLocation + (DirectionVector * DesiredDistance);

				WidgetLocation.Z = 100.0f;

				FVector2D ScreenLocation;
				UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WidgetLocation, ScreenLocation);

				int32 RoundDamage = int32(round(Damage));
				wDamage->AddToViewport();
				wDamage->UpdateDamage(RoundDamage);
				wDamage->SetPositionInViewport(ScreenLocation, true);

				PlayHitReaction();
			}
		}
	}
}

void AMyPlayer::EquipSword()
{
	//애니메이션 + 소켓 위치 잡아서 Attach

	if (GreatSwordClass)
	{
		if (EquippedGreatSword)
		{
			PlayAnimMontage(EquipSwordMontage, 1.0f);
			bIsEquipped = true;
			GetWorld()->GetTimerManager().SetTimer(StepHandle, this, &AMyPlayer::OnTimer, 1.0f, true);
		}
	}
}

void AMyPlayer::UnEquipSword()
{
	//애니메이션 + Deattach
	if (GreatSwordClass)
	{
		if (EquippedGreatSword)
		{
			PlayAnimMontage(UnEquipSwordMontage, 1.0f);
		}
	}
}

void AMyPlayer::AttachSword()
{
	if (GreatSwordClass)
	{
		FVector SpawnLocation = FVector::ZeroVector;
		FRotator SpawnRotation = FRotator::ZeroRotator;

		EquippedGreatSword = GetWorld()->SpawnActor<AGreatSword>(GreatSwordClass, SpawnLocation, SpawnRotation);
		if (EquippedGreatSword)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			EquippedGreatSword->AttachToComponent(GetMesh(), AttachmentRules, TEXT("Weapon_Socket"));
		}
	}
}

void AMyPlayer::OnTimer()
{
	++TimeCount;

	if (TimeCount >= 15)
	{
		UnEquipSword();
		GetWorld()->GetTimerManager().ClearTimer(StepHandle);
		TimeCount = 0;
	}
}

void AMyPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();

	const ULostArkPlayerAttributeSet* CurrentAttributeSet = AbilitySystemComponent->GetSet<ULostArkPlayerAttributeSet>();
	if (CurrentAttributeSet)
	{
		CurrentAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);
		CurrentAttributeSet->OnGetDamage.AddDynamic(this, &ThisClass::OnGetDamage);
	}

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		AbilitySystemComponent->GiveAbility(StartSpec);
	}

	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		AbilitySystemComponent->GiveAbility(StartSpec);
	}

	APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
	ALostArkPlayerController* LostArkPlayerController = Cast<ALostArkPlayerController>(PlayerController);

	LostArkPlayerController->SetupGASInputComponent();

	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent->HasMatchingGameplayTag(LOSTARKTAG_CHARACTER_ISDEAD))
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(LOSTARKTAG_CHARACTER_ISDEAD);
		}
	}
}

void AMyPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the Client
	InitAbilityActorInfo();
}

float AMyPlayer::GetPlayerLevel()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	check(LostArkPlayerState);
	return LostArkPlayerState->GetPlayerLevel();
}

void AMyPlayer::LevelUP()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(GetController());
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	check(LostArkPlayerState);
	LostArkPlayerState->LevelUP();
	//나이아가라

	FVector Location = GetActorLocation() - FVector(0.f, 0.f, 80.f);
	/*NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
		LevelUPNiagara,
		GetMesh(),
		FName("LevelUP"),
		Location,
		FRotator::ZeroRotator,
		FVector(1.0f),
		EAttachLocation::SnapToTarget,
		true,
		ENCPoolMethod::None,
		true
		);*/

	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		LevelUPNiagara,
		Location,
		FRotator::ZeroRotator,
		FVector(1.0f)
	);

	//위젯
	PlayerHUD->SpawnLevelUPWidgetWithAnimation(GetActorLocation());

	ApplyEffectToSelf(UpdateRequiredEXPEffectClass, GetPlayerLevel() + 1);
	InitializeDefaultAttributes();
	PlayerHUD->OverlayWidget->WBPExpBattle->UpdateBattleLevel(GetPlayerLevel());
	PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateBattleLevel(GetPlayerLevel());
}

float AMyPlayer::GetPlayerExpeditionLevel()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	check(LostArkPlayerState);
	return LostArkPlayerState->GetPlayerExpeditionLevel();
}

void AMyPlayer::ExpeditionLevelUP()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(GetController());
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	check(LostArkPlayerState);
	LostArkPlayerState->ExpeditionLevelUP();
	ApplyEffectToSelf(UpdateExpeditionRequiredEXPEffectClass, GetPlayerExpeditionLevel() + 1);
	PlayerHUD->OverlayWidget->WBPExpBattle->UpdateExpeditionLevel(GetPlayerExpeditionLevel());
	PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateExpeditionLevel(GetPlayerExpeditionLevel());
}

void AMyPlayer::InitAbilityActorInfo()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	check(LostArkPlayerState);
	LostArkPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(LostArkPlayerState, this);
	Cast<ULostArkAbilitySystemComponent>(LostArkPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = Cast<ULostArkAbilitySystemComponent>(LostArkPlayerState->GetAbilitySystemComponent());
	AttributeSet = LostArkPlayerState->GetAttributeSet();

	if (ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(GetController()))
	{
		if (APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD()))
		{
			PlayerHUD->InitOverlay(PC, LostArkPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}

void AMyPlayer::MaintainStatus(UChaosDungeonGameInstance* GameInstance)
{
	if (GameInstance)
	{
		ALostArkPlayerState* MyPlayerState = Cast<ALostArkPlayerState>(GetPlayerState());
		MyPlayerState->SetPlayerLevel(GameInstance->PlayerBattleLevel);
		MyPlayerState->SetPlayerExpeditionLevel(GameInstance->PlayerExpeditionLevel);

		ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());

		if (PlayerHUD)
		{
			if (PlayerHUD->OverlayWidget)
			{
				if (PlayerHUD->OverlayWidget->WBPProgress)
				{
					PlayerHUD->OverlayWidget->WBPProgress->ProgressValue->SetText(FText::FromString(GameInstance->ProgressValue));
					PlayerHUD->OverlayWidget->WBPProgress->ChaosDungeonProgressBar->SetPercent(GameInstance->CurrentProgress);
				}
				if (PlayerHUD->OverlayWidget->WBPExpBattle)
				{
					PlayerHUD->OverlayWidget->WBPExpBattle->UpdateBattleLevel(GameInstance->PlayerBattleLevel);
					FTimerHandle LoadTimer;
					GetWorld()->GetTimerManager().SetTimer(
						LoadTimer, [this]() {
							UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
							ALostArkPlayerState* PlayerState = Cast<ALostArkPlayerState>(GetPlayerState());
							ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
							APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());

							PlayerHUD->OverlayWidget->WBPExpBattle->BattleEXPBar->SetPercent(GameInstance->PlayerBattleEXPBarPercent);
						}, 0.1f, false
					);

					Cast<ULostArkPlayerAttributeSet>(MyPlayerState->GetAttributeSet())->SetEXP(GameInstance->PlayerBattleEXP);
					Cast<ULostArkPlayerAttributeSet>(MyPlayerState->GetAttributeSet())->SetExpeditionEXP(GameInstance->PlayerExpeditionEXP);
					PlayerHUD->OverlayWidget->WBPExpBattle->UpdateExpeditionLevel(GameInstance->PlayerExpeditionLevel);

				}
				if (PlayerHUD->OverlayWidget->WBPExpExpedition)
				{
					PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateBattleLevel(GameInstance->PlayerBattleLevel);
					FTimerHandle LoadTimer;
					GetWorld()->GetTimerManager().SetTimer(
						LoadTimer, [this]() {
							UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
							ALostArkPlayerState* PlayerState = Cast<ALostArkPlayerState>(GetPlayerState());
							ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
							APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());

							PlayerHUD->OverlayWidget->WBPExpExpedition->ExpeditionEXPBar->SetPercent(GameInstance->PlayerExpeditionEXPBarPercent);
						}, 0.1f, false
					);

					PlayerHUD->OverlayWidget->WBPExpExpedition->UpdateExpeditionLevel(GameInstance->PlayerExpeditionLevel);
				}
			}
		}

		UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(MaintainRequiredEXPEffectClass, 1.0f, ASC->MakeEffectContext());


		if (SpecHandle.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_REQUIREDEXP, GameInstance->PlayerBattleRequiredEXP);
			SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXPEDITIONREQUIREDEXP, GameInstance->PlayerExpeditionRequiredEXP);

			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}

		FTimerHandle DelayTimer;
		GetWorld()->GetTimerManager().SetTimer(DelayTimer, [this] {
			UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(MaintainEXPEffectClass, 1.0f, ASC->MakeEffectContext());
			UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
			if (SpecHandle.IsValid())
			{
				SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXP, GameInstance->PlayerBattleEXP);
				SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXPEDITIONEXP, GameInstance->PlayerExpeditionEXP);

				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}, 1.0f, false);


		SpecHandle = ASC->MakeOutgoingSpec(MaintainCurrentLMEffectClass, 1.0f, ASC->MakeEffectContext());
		if (SpecHandle.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_VITAL_CURRENTLIFEPOINT, GameInstance->PlayerCurrentLifePoint);
			SpecHandle.Data->SetSetByCallerMagnitude(LOSTARKTAG_ATTRIBUTES_PLAYER_VITAL_CURRENTMANAPOINT, GameInstance->PlayerCurrentManaPoint);

			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}

		ApplyEffectToSelf(MaintainStatusEffectClass, GetPlayerLevel());

		ApplyEffectToSelf(MaintainMaxLifePointEffectClass, GetPlayerLevel());
	}
}