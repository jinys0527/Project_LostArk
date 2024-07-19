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
#include "GreatSword.h"
#include "Engine/World.h"

AMyPlayer::AMyPlayer() : ABaseCharacter()
{
	//HP, 생명력
	Stat.HP = 3000.f;
	Stat.HPCoefficient = 2.2f;
	Stat.MaxLifePoint = Stat.HP * Stat.HPCoefficient;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

	//MP
	Stat.MP = 1000.f;

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
	
}

void AMyPlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyPlayer::PlayDead()
{
	//애니메이션
}

void AMyPlayer::PlayHitReaction()
{
	//애니메이션
}

void AMyPlayer::Move()
{
	//애니메이션
}

void AMyPlayer::Attack()
{
	//애니메이션
	if (!bIsEquipped)
	{
		EquipSword();
	}
	else if (bIsEquipped) //장착한 상태일때
	{
		if (bIsAttacking) // 공격중이면 return
		{
			return;
		}
		TimeCount = 0;
		PlayAnimMontage(AttackMontage);
	}
	//데미지 처리 + 위젯 소환
}

void AMyPlayer::PlayResurrection()
{
	//애니메이션
}

float AMyPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (Stat.CurrentLifePoint > 0)
	{
		PlayHitReaction();
		Stat.CurrentLifePoint -= Damage;

	}
	else
	{
		PlayDead();
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->DisableInput(PC);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return 0.0f;
}

void AMyPlayer::Resurrection()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PlayResurrection();
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
			FTimerHandle TimerHandle;
			float GravityTime = 0.6f;
			GetWorld()->GetTimerManager().SetTimer(StepHandle, this, &AMyPlayer::OnTimer, 1.0f, true);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
					EquippedGreatSword->AttachToComponent(GetMesh(), AttachmentRules, TEXT("Weapon_Right"));
					bIsEquipped = true;
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}), GravityTime, false);
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
			FTimerHandle TimerHandle;
			float GravityTime = 0.6f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
					EquippedGreatSword->AttachToComponent(GetMesh(), AttachmentRules, TEXT("Weapon_Socket"));
					bIsEquipped = false;
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}), GravityTime, false);
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

void AMyPlayer::EquipTimer()
{
	++EquipTimeCount;

	if (TimeCount >= 2)
	{
		GetWorld()->GetTimerManager().ClearTimer(DrawHandle);
		EquipTimeCount = 0;
	}
}