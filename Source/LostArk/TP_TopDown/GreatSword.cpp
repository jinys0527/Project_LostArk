// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSword.h"
#include "Monster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayer.h"


AGreatSword::AGreatSword() : AWeapon()
{
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Weapon(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Sword_EditPivot/SM_Sword_EditedPivot_.SM_Sword_EditedPivot_'"));

	Weapon->SetupAttachment(RootComponent);
	Weapon->SetGenerateOverlapEvents(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Weapon->SetCollisionProfileName("Weapon");
	Weapon->OnComponentBeginOverlap.AddDynamic(this, &Super::OnOverlapBegin);
	Weapon->OnComponentEndOverlap.AddDynamic(this, &Super::OnOverlapEnd);

	bIsAttack = false;

	if (SM_Weapon.Succeeded())
	{
		Weapon->SetStaticMesh(SM_Weapon.Object);
	}
	WeaponATK = 3000.0f;
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
		UGameplayStatics::ApplyDamage(Monster, Player->CalcDamage(Player->Stat.ATK, Monster->Stat.Block), PC, this, UDamageType::StaticClass());
	}
}

void AGreatSword::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
