// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AMyPlayer::AMyPlayer()
{
	Super();

	//HP, �����
	Stat.HP = 3000.f;
	Stat.HPCoefficient = 2.2f;
	Stat.LifePoint = Stat.HP * Stat.HPCoefficient;
	Stat.CurrentLifePoint = Stat.LifePoint;

	//MP
	Stat.MP = 1000.f;

	//���ݷ�
	Stat.Ability = 4500.f;
	Stat.WeaponATK = 3000.f;
	Stat.ATK = (float)FMath::Sqrt(((double)Stat.Ability * (double)Stat.WeaponATK) / (double)6);

	//����
	Stat.DEFCoefficient = 1.1f;
	Stat.ArmorDEF = 900.f;
	Stat.DEF = Stat.DEFCoefficient * Stat.ArmorDEF;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//ġ��Ÿ ����
	Stat.CriticalHitRate = 0.3f;
	Stat.CriticalDamageIncrease = 2.0f;

	//�ó���
	Stat.DamageIncrease = 1.0f;

	//����ġ
	Stat.EXP = 0.0f;

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

void AMyPlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyPlayer::PlayDead()
{
	//�ִϸ��̼�
}

void AMyPlayer::PlayHitReaction()
{
	//�ִϸ��̼�
}

void AMyPlayer::Move()
{
	//�ִϸ��̼�
}

void AMyPlayer::Attack()
{
	//�ִϸ��̼�
}

void AMyPlayer::PlayResurrection()
{
	//�ִϸ��̼�
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
		Stat.CurrentLifePoint = Stat.LifePoint;
		PC->EnableInput(PC);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
