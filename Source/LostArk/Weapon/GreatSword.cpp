// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSword.h"
#include "../Monster/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "../Player/MyPlayer.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/GameplayAbility/GA_Attack.h"


AGreatSword::AGreatSword() : AWeapon()
{
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

	RootComponent = Weapon;
	Weapon->SetGenerateOverlapEvents(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Weapon->SetCollisionProfileName("Weapon");
	Weapon->OnComponentBeginOverlap.AddDynamic(this, &Super::OnOverlapBegin);
	Weapon->OnComponentEndOverlap.AddDynamic(this, &Super::OnOverlapEnd);

	WeaponATK = 3000.0f;

	bIsOverlapped = false;
}

void AGreatSword::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
	AMyPlayer* Player = Cast<AMyPlayer>(Character);

	AMonster* Monster = Cast<AMonster>(OtherActor);
	if (Monster)
	{
		Player->Target.Add(Monster);
		if (!Monster->bIsHitted && Player->bIsAttack)
		{
			int32 RandomValue = FMath::RandRange(1, 10);

			if (RandomValue <= 3)
			{
				Player->bIsCritical = true;
				UAbilitySystemComponent* AbilitySystemComponent = Player->GetAbilitySystemComponent();
				if (AbilitySystemComponent)
				{
					AbilitySystemComponent->TryActivateAbilityByClass(UGA_Attack::StaticClass());
				}
				Monster->bIsHitted = true;
				bIsOverlapped = true;
			}
			else
			{
				Player->bIsCritical = false;
				UAbilitySystemComponent* AbilitySystemComponent = Player->GetAbilitySystemComponent();
				if (AbilitySystemComponent)
				{
					AbilitySystemComponent->TryActivateAbilityByClass(UGA_Attack::StaticClass());
				}
				Monster->bIsHitted = true;
				bIsOverlapped = true;
			}
		}
		else if (Monster->bIsHitted && bIsOverlapped)
		{
			return;
		}
	}
}

void AGreatSword::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
