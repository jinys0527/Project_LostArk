// Fill out your copyright notice in the Description page of Project Settings.


#include "../ChaosDungeon/MonsterSpawner.h"
#include "../ChaosDungeon/ChaosDungeonGameState.h"
#include "../Monster/Monster.h"
#include "../Monster/NamedMonster.h"
#include "../Monster/BossMonster.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Center = GetActorLocation();
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterSpawner::SpawnMonster(EMonsterType MonsterType)
{
	if (MonsterType == EMonsterType::Common)
	{
		MaxRadius = CommonMaxRadius;
	}
	else if (MonsterType == EMonsterType::Named)
	{
		MaxRadius = NamedMaxRadius;
	}
	Radius = FMath::FRandRange(0.0f, MaxRadius);
	Angle = FMath::FRandRange(0.0f, 360.0f);

	float SpawnX = Center.X + FMath::Cos(FMath::DegreesToRadians(Angle)) * Radius;
	float SpawnY = Center.Y + FMath::Sin(FMath::DegreesToRadians(Angle)) * Radius;
	float SpawnZ = Center.Z;

	FVector SpawnLocation(SpawnX, SpawnY, SpawnZ);

	FRotator SpawnRotation = FRotator::ZeroRotator;

	UWorld* World = GetWorld();
	
	if (World)
	{
		AGameStateBase* CurrentState = World->GetGameState();
		if (CurrentState)
		{
			AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(CurrentState);

			switch (MonsterType)
			{
			case EMonsterType::Boss:
				MonsterSizeRadius = 62.0f;
				if (CheckValidLocation(SpawnLocation, MonsterSizeRadius))
				{
					World->SpawnActor<ABossMonster>(ABossMonster::StaticClass(), Center, SpawnRotation);
					++ChaosDungeonState->CurrentMonsterCount;
				}
				break;
			case EMonsterType::Common:
				MonsterSizeRadius = 48.0f;
				
				if ((ChaosDungeonState->CurrentMonsterCount < ChaosDungeonState->MonsterMaxSpawnLimit) && ChaosDungeonState->StageCommonCount < ChaosDungeonState->StageCommonLimit)
				{
					if (CheckValidLocation(SpawnLocation, MonsterSizeRadius))
					{
						World->SpawnActor<AMonster>(AMonster::StaticClass(), SpawnLocation, SpawnRotation);
						++ChaosDungeonState->CurrentMonsterCount;
						++ChaosDungeonState->StageCommonCount;
					}
				}
				break;
			case EMonsterType::Named:
				MonsterSizeRadius = 50.0f;
				if (((ChaosDungeonState->CurrentMonsterCount + ChaosDungeonState->StageNamedCount) < ChaosDungeonState->MonsterMaxSpawnLimit) && (ChaosDungeonState->StageNamedCount < ChaosDungeonState->StageNamedLimit))
				{
					if (CheckValidLocation(SpawnLocation, MonsterSizeRadius))
					{
						World->SpawnActor<ANamedMonster>(ANamedMonster::StaticClass(), SpawnLocation, SpawnRotation);
						++ChaosDungeonState->CurrentMonsterCount;
						++ChaosDungeonState->StageNamedCount;
					}
				}
				break;
			}
		}
	}
}

bool AMonsterSpawner::CheckValidLocation(FVector NewSpawnLocation, float SpawnRadius)
{
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SpawnRadius);

	bool bIsValidLocation = !GetWorld()->OverlapBlockingTestByChannel(NewSpawnLocation, FQuat::Identity, ECC_WorldStatic, CollisionShape);

	return bIsValidLocation;
}
