// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class LOSTARK_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void NotifyAbilityStart();

	void NotifyAbilityEnd();

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 30;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
};
