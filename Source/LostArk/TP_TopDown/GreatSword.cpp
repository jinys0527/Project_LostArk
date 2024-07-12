// Fill out your copyright notice in the Description page of Project Settings.


#include "GreatSword.h"

AGreatSword::AGreatSword() : AWeapon()
{
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Weapon(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Sword_EditPivot/SM_Sword_EditedPivot_.SM_Sword_EditedPivot_'"));

	if (SM_Weapon.Succeeded())
	{
		Weapon->SetStaticMesh(SM_Weapon.Object);
	}
}
