// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster/MonsterType.h"
#include "MonsterSpawner.generated.h"

class AMonster;
class ANamedMonster;

UCLASS()
class LOSTARK_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	float Radius;

	float Angle;
	
	float MaxRadius;

	FVector Center;

	float MonsterSizeRadius;

	float CommonMaxRadius = 300.0f;

	float NamedMaxRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonster> MonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANamedMonster> NamedMonsterClass;

	void SpawnMonster(EMonsterType MonsterType);
};
