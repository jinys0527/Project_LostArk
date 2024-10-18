// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaosDungeonCore.generated.h"

class AMonsterSpawner;
class ANamedMonster;

UCLASS()
class LOSTARK_API AChaosDungeonCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChaosDungeonCore();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hitted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AMonsterSpawner* Spawner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonsterSpawner> MonsterSpawnerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANamedMonster> NamedMonsterClass;
};
