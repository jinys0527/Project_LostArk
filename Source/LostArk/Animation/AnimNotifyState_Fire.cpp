// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_Fire.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "../Player/MyPlayer.h"
#include "../Monster/BossMonster.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UAnimNotifyState_Fire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ElapsedTime = 0.0f;
	AActor* Owner = MeshComp->GetOwner();
	if (Owner)
	{
		UAbilitySystemComponent* ASC = Owner->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC && GameplayCueTag.IsValid())
		{
			ASC->ExecuteGameplayCue(GameplayCueTag, FGameplayCueParameters());
		}
	}
}

void UAnimNotifyState_Fire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	ABossMonster* Boss = Cast<ABossMonster>(MeshComp->GetOwner());

	ElapsedTime += FrameDeltaTime;

	FVector StartLocation = MeshComp->GetSocketLocation("FireAttack");
	FVector EndLocation = StartLocation + (MeshComp->GetSocketTransform("FireAttack").GetRotation().GetForwardVector() * 500.f);
	FRotator BoxRotation = FRotator::ZeroRotator;
	FHitResult HitResult;
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);
	//CollisionChannel::ECC_WorldDynamic); //충돌처리할 거 지정
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(Boss);

	if (ElapsedTime >= 0.04f)
	{
		bool bHit = UKismetSystemLibrary::BoxTraceSingle(
			MeshComp->GetWorld(),
			StartLocation,
			EndLocation,
			FVector(30, 30, 30),
			BoxRotation,
			TraceChannel,
			false,
			IgnoreActor,
			EDrawDebugTrace::None,
			HitResult,
			true,
			FLinearColor::Blue,
			FLinearColor::Green,
			0.5f
		);

		if (bHit)
		{
			if (AActor* OtherActor = HitResult.GetActor())
			{
				AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
				if (Player)
				{
					UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent();
					UAbilitySystemComponent* SourceASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
					if (ASC && SourceASC)
					{
						FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(FireDamage, 1, SourceASC->MakeEffectContext());
						SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
						//SpecHandle = SourceASC->MakeOutgoingSpec(BurningDamage, 1, SourceASC->MakeEffectContext());
						//SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
					}
				}
			}
		}
		ElapsedTime = 0.0f;
	}
}

void UAnimNotifyState_Fire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (Owner)
	{
		UAbilitySystemComponent* ASC = Owner->FindComponentByClass<UAbilitySystemComponent>();

		if (ASC && GameplayCueTag.IsValid())
		{
			ASC->RemoveGameplayCue(GameplayCueTag);
		}
	}
}
