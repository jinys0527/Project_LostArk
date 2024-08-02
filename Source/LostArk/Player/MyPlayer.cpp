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

AMyPlayer::AMyPlayer() : ABaseCharacter()
{
	//HP, 생명력
	Stat.HP = 3000.f;
	Stat.HPCoefficient = 2.2f;
	Stat.MaxLifePoint = Stat.HP * Stat.HPCoefficient;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

	//MP
	Stat.MaxMP = 1000.f;
	Stat.CurrentMP = Stat.MaxMP;

	//공격력
	Stat.Ability = 4500.f;
	WeaponATK = 3000.0f;
	Stat.ATK = (float)FMath::Sqrt(((double)Stat.Ability * (double)WeaponATK) / (double)6);

	//방어력
	Stat.DEFCoefficient = 1.1f;
	Stat.ArmorDEF = 900.f;
	Stat.DEF = Stat.DEFCoefficient * Stat.ArmorDEF;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//치명타 관련
	Stat.CriticalHitRate = 0.3f;
	Stat.CriticalDamageIncrease = 2.0f;

	//시너지
	Stat.DamageIncrease = 1.0f;

	//경험치
	Stat.EXP = 0.0f;

	bIsEquipped = false;

	bIsAttacking = false;

	bIsCritical = false;

	SetPlayerState(ECharacterState::Idle);

	static ConstructorHelpers::FClassFinder<AGreatSword> GreatSword(TEXT("/Script/Engine.Blueprint'/Game/Weapons/Blueprints/BP_GreatSword.BP_GreatSword_C'"));

	if (GreatSword.Succeeded() && GreatSword.Class != NULL)
	{
		GreatSwordClass = GreatSword.Class;
	}

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
	PlayerHUD->PlayerStatus->UpdateHPBar(Stat.CurrentLifePoint, Stat.MaxLifePoint);
	PlayerHUD->PlayerStatus->UpdateMPBar(Stat.CurrentMP, Stat.MaxMP);

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		PlayerAnimInstance = Cast<UAnimInstance_Player>(MeshComp->GetAnimInstance());
	}

	FTimerHandle UpdateStatusTimer;
	FTimerHandle RegenTimer;

	GetWorld()->GetTimerManager().SetTimer(RegenTimer, this, &AMyPlayer::Regen, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(UpdateStatusTimer, [this, PlayerHUD]()
		{
			UpdateStatus(PlayerHUD);
		}, 0.5f, true);
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
	int32 RandomNumber = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("Death_%d"), RandomNumber);
	PlayAnimMontage(DeathMontage, 1.0f, FName(*SectionName));
}

void AMyPlayer::PlayHitReaction()
{
	if (CurrentState == ECharacterState::Idle)
	{
		PlayAnimMontage(HitReactionMontage, 1.0f);
	}
	else if (CurrentState == ECharacterState::Battle)
	{
		PlayAnimMontage(HitReactionBattleMontage, 1.0f);
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
			PlayAnimMontage(AttackMontage);
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

float AMyPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(GetController());
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (Stat.CurrentLifePoint > 0)
	{
		Stat.CurrentLifePoint -= Damage;
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
				}
			}
			if (PlayerHUD->PlayerStatusClass)
			{
				if (PlayerHUD->PlayerStatus)
				{
					if (PlayerHUD->PlayerStatus->GetCurrentHP() != Stat.CurrentLifePoint)
					{
						PlayerHUD->PlayerStatus->UpdateHPBar(Stat.CurrentLifePoint, Stat.MaxLifePoint);
					}
					if (PlayerHUD->PlayerStatus->GetCurrentMP() != Stat.CurrentMP)
					{
						PlayerHUD->PlayerStatus->UpdateMPBar(Stat.CurrentMP, Stat.MaxMP);
					}
				}
			}
		}

		PlayHitReaction();

	}
	else
	{
		Tags.Remove(FName("Player"));
		if (PC)
		{
			PC->DisableInput(PC);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		isAlive = false;
		PlayDead();
		SetPlayerState(ECharacterState::Death);
	}

	return 0.0f;
}

void AMyPlayer::Resurrection()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PlayResurrection();
		Tags.AddUnique(FName("Player"));
		SetPlayerState(ECharacterState::Idle);
		Stat.CurrentLifePoint = Stat.MaxLifePoint;
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
			WeaponATK = EquippedGreatSword->WeaponATK;
			Stat.ATK = (float)FMath::Sqrt(((double)Stat.Ability * (double)WeaponATK) / (double)6);
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			EquippedGreatSword->AttachToComponent(GetMesh(), AttachmentRules, TEXT("Weapon_Socket"));
		}
	}
}

void AMyPlayer::OnTimer()
{
	++TimeCount;

	if (TimeCount >= 5)
	{
		UnEquipSword();
		GetWorld()->GetTimerManager().ClearTimer(StepHandle);
		TimeCount = 0;
	}
}

void AMyPlayer::Regen()
{
	if (CurrentState == ECharacterState::Idle ||
		CurrentState == ECharacterState::Battle)
	{
		Stat.CurrentLifePoint += ceil(Stat.MaxLifePoint * 0.0006f);
		Stat.CurrentMP += ceil(Stat.MaxMP * 0.0006f);
	}
}

void AMyPlayer::UpdateStatus(APlayerHUD* PlayerHUD)
{
	PlayerHUD->PlayerStatus->UpdateHPBar(Stat.CurrentLifePoint, Stat.MaxLifePoint);
	PlayerHUD->PlayerStatus->UpdateMPBar(Stat.CurrentMP, Stat.MaxMP);
}