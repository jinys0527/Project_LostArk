// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterSpawner.h"
#include "BossMonsterSpawner.generated.h"

class ABossMonster;

/**
 * 
 */
UCLASS()
class LOSTARK_API ABossMonsterSpawner : public AMonsterSpawner
{
	GENERATED_BODY()
	
public:
	ABossMonsterSpawner();

	float MonsterSizeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABossMonster> BossClass;

	ABossMonster* SpawnBossMonster(FVector SpawnLocation, FRotator SpawnRotation);
};
