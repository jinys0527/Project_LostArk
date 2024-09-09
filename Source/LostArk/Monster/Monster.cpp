// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GameFramework/Character.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "../Widget/DamageWidget.h"
#include "../Player/MyPlayer.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/HeadMountHPWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "BossMonster.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "../Widget/HeadMountHPWidget.h"
#include "NamedMonster.h"
#include "BossMonster.h"
#include "../ChaosDungeon/ChaosDungeonGameState.h"
#include "../Widget/ProgressWidget.h"
#include "../Animation/AnimInstance_Monster.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkMonsterAttributeSet.h"
#include "../AbilitySystem/GameplayAbility/GA_Attack.h"
#include "../Widget/OverlayWidget.h"
#include "GameplayAbilitySpec.h"
#include "../Tag/LostArkGameplayTag.h"

AMonster::AMonster() : ABaseCharacter()
{
	Name = "Common Monster";

	AnimInstance = Cast<UAnimInstance_Monster>(GetMesh()->GetAnimInstance());

	HeadMountHPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadMountHPBar"));
	HeadMountHPBarWidget->SetupAttachment(RootComponent);
	HeadMountHPBarWidget->SetDrawAtDesiredSize(true);
	HeadMountHPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HeadMountHPBarWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	HeadMountHPBarWidget->SetCastShadow(false);
	HeadMountHPBarWidget->SetHiddenInGame(true);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WBP_HP_HeadMount'"));
	if (WidgetClassFinder.Succeeded())
	{
		HeadMountHPBarWidget->SetWidgetClass(WidgetClassFinder.Class);
	}

	MonsterType = EMonsterType::Common;

	bIsAttack = false;

	bIsHitted = false;

	AIControllerClass = MonsterAIControllerClass;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AbilitySystemComponent = CreateDefaultSubobject<ULostArkAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<ULostArkMonsterAttributeSet>(TEXT("AttributeSet"));
}

void AMonster::PlayDead()
{
	PlayAnimMontage(DeathMontage, 1.0f);
}

void AMonster::Attack()
{
	PlayAnimMontage(AttackMontage, 1.0f);
}

void AMonster::PlayHitReaction()
{
	if (AnimInstance)
	{
		if (!AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			PlayAnimMontage(HitReactionMontage, 1.0f);
		}
	}
}

void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();

	ULostArkMonsterAttributeSet* CurrentAttributeSet = Cast<ULostArkMonsterAttributeSet>(GetAttributeSet());
	
	if (CurrentAttributeSet)
	{
		CurrentAttributeSet->bIsSet = true;
		CurrentAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::OnOutOfHealth);
		CurrentAttributeSet->OnGetDamage.AddDynamic(this, &ThisClass::OnGetDamage);
	}

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		AbilitySystemComponent->GiveAbility(StartSpec);
	}
}

void AMonster::OnOutOfHealth()
{
	SetDead();
}

void AMonster::OnGetDamage(AActor* DamageCauser, float Damage)
{
	AMyPlayer* Player = Cast<AMyPlayer>(DamageCauser);
	if (Player)
	{
		ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(Player->GetController());
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
		if (PlayerHUD)
		{
			if (DamageClass)
			{
				wDamage = CreateWidget<UDamageWidget>(PC, DamageClass);
				if (wDamage)
				{
					wDamage->SynchronizeProperties();

					if (Player && Player->bIsCritical == true)
					{
						wDamage->DamageValue->SetColorAndOpacity(FLinearColor(0.83077, 0.617207, 0.024158));
					}
					else if (Player && Player->bIsCritical != true)
					{
						wDamage->DamageValue->SetColorAndOpacity(FLinearColor(0.871367, 0.863157, 0.863157));
					}
					wDamage->DamageValue->SetShadowOffset(FVector2D(0, 0));
					wDamage->DamageValue->SetShadowColorAndOpacity(FLinearColor::Transparent);

					FVector MonsterLocation = GetActorLocation();
					FVector PlayerLocation = DamageCauser->GetActorLocation();

					FVector DirectionVector = MonsterLocation - PlayerLocation;
					DirectionVector.Normalize();

					float DesiredDistance = 30.0f;
					WidgetLocation = MonsterLocation + (DirectionVector * DesiredDistance);

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

			if (HeadMountHPBarWidget && MonsterType != EMonsterType::Boss)
			{
				HeadMountHPBarWidget->SetHiddenInGame(false);
			}
		}
	}

}

void AMonster::SetDead()
{
	Super::SetDead();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Target);
	if (MyPlayer)
	{
		ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(MyPlayer->GetController());
		if (PC)
		{
			APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
			if (PlayerHUD && PlayerHUD->OverlayWidget)
			{
				if (MonsterType == EMonsterType::Common)
				{
					PlayerHUD->OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Collapsed);
				}
				else if (MonsterType == EMonsterType::Named)
				{
					PlayerHUD->OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Collapsed);
				}
				else if (MonsterType == EMonsterType::Boss)
				{
					PlayerHUD->OverlayWidget->WBPHPBoss->SetVisibility(ESlateVisibility::Collapsed);
				}
			}
		}

		UAbilitySystemComponent* PlayerASC = MyPlayer->GetAbilitySystemComponent();
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddInstigator(this, GetController());
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, Level, EffectContext);
		if (EffectSpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), PlayerASC);
		}

	}

	

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);

	AGameStateBase* CurrentState = GetWorld()->GetGameState();
	if (CurrentState)
	{
		AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(CurrentState);
		--ChaosDungeonState->CurrentMonsterCount;
	}

	isAlive = false;
	OnMonsterDead.Broadcast();
	OnMonsterDeadWithType.Broadcast(MonsterType);
	OnMonsterDeadWithMonster.Broadcast(this);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	if (UHeadMountHPWidget* HeadMountHP = Cast<UHeadMountHPWidget>(HeadMountHPBarWidget->GetUserWidgetObject()))
	{
		HeadMountHP->SetWidgetController(this);
	}

	if (const ULostArkMonsterAttributeSet* MonsterAttributeSet = Cast< ULostArkMonsterAttributeSet>(AttributeSet))
	{
		OnMonsterCurrentLifePointChanged.Broadcast(MonsterAttributeSet->GetMonsterCurrentLifePoint());
		OnMonsterMaxLifePointChanged.Broadcast(MonsterAttributeSet->GetMonsterMaxLifePoint());
	}
}

void AMonster::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<ULostArkAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	UOverlayWidgetController* OverlayWidgetController = Cast<UOverlayWidgetController>(PlayerHUD->OverlayWidget->WidgetController);
	OverlayWidgetController->BindToMonsterEvents(this);
	InitializeDefaultAttributes();
	BroadcastLifePoint();
}

void AMonster::BroadcastLifePoint()
{
	if (AttributeSet)
	{
		ULostArkMonsterAttributeSet* MonsterAttributeSet = Cast<ULostArkMonsterAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MonsterAttributeSet->GetMonsterCurrentLifePointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMonsterCurrentLifePointChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MonsterAttributeSet->GetMonsterMaxLifePointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMonsterMaxLifePointChanged.Broadcast(Data.NewValue);
		}
	);
	}
}
