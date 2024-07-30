// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GreatSword.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API AGreatSword : public AWeapon
{
	GENERATED_BODY()
public:
	AGreatSword();
	
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	) override;

	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) override;

	uint8 bIsOverlapped : 1;
};
