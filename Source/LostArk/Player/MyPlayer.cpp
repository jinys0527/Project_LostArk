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
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/PlayerStatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Animation/AnimInstance_Player.h"
#include "../Player/LostArkPlayerState.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../Tag/LostArkGameplayTag.h"

AMyPlayer::AMyPlayer() : ABaseCharacter()
{
	bIsEquipped = false;

	bIsAttacking = false;

	bIsCritical = false;

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

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetController());
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
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
	if (CurrentState == ECharacterState::Idle)
	{
		PlayAnimMontage(HitReactionMontage, 1.0f);
	}
	if (AnimInstance)
	{
		if ((CurrentState == ECharacterState::Battle || CurrentState == ECharacterState::Attacking || CurrentState == ECharacterState::Combat) && !AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			PlayAnimMontage(HitReactionBattleMontage, 1.0f);
		}
	}
}

void AMyPlayer::Attack()
{
	//애니메이션
	if (bIsEquipped) //장착한 상태일때
	{
		if (bIsAttacking) // 공격중이면 return
		{
			return;
		}
		else if (CurrentState != ECharacterState::Skilling &&
			CurrentState != ECharacterState::Stunned &&
			CurrentState != ECharacterState::Dashing &&
			CurrentState != ECharacterState::GetHitting &&
			CurrentState != ECharacterState::Moving &&
			CurrentState != ECharacterState::Idle)
		{
			TimeCount = 0;
		}
	}
	else if (!bIsEquipped)
	{
		EquipSword();
		return;
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
		Tags.Remove(FName("Player"));
		DisableInput(PlayerController);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AMyPlayer::OnOutOfHealth()
{
	SetDead();
}

void AMyPlayer::OnGetDamage(AActor* DamageCauser, float Damage)
{
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetController());
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

void AMyPlayer::Resurrection()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PlayResurrection();
		Tags.AddUnique(FName("Player"));
		SetPlayerState(ECharacterState::Idle);
		PC->EnableInput(PC);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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

	if (TimeCount >= 8)
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

	check(AbilitySystemComponent);
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetPlayerLevel(), ContextHandle);

	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
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
	ATP_TopDownPlayerController* LostArkPlayerController = Cast<ATP_TopDownPlayerController>(PlayerController);
	LostArkPlayerController->SetupGASInputComponent();
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
	check(LostArkPlayerState);
	LostArkPlayerState->LevelUP();
	check(AbilitySystemComponent);
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetPlayerLevel(), ContextHandle);
}

void AMyPlayer::InitAbilityActorInfo()
{
	ALostArkPlayerState* LostArkPlayerState = GetPlayerState<ALostArkPlayerState>();
	check(LostArkPlayerState);
	LostArkPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(LostArkPlayerState, this);
	Cast<ULostArkAbilitySystemComponent>(LostArkPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = Cast<ULostArkAbilitySystemComponent>(LostArkPlayerState->GetAbilitySystemComponent());
	AttributeSet = LostArkPlayerState->GetAttributeSet();

	if (ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetController()))
	{
		if (APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD()))
		{
			PlayerHUD->InitOverlay(PC, LostArkPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}
