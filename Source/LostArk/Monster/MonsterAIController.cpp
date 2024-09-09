// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Player/MyPlayer.h"

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		AMyPlayer* Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent)
		{
			if (GetPawn())
			{
				BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
			}
			
			BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());

			BlackboardComponent->SetValueAsBool(TEXT("AbilityEnd"), true);
		}
	}
	AMyPlayer* Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AMonsterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyPlayer* Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//MoveToActor(Player, AcceptanceRadius);
}

void AMonsterAIController::NotifyAbilityStart()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsBool(TEXT("AbilityEnd"), false);
	}
}

void AMonsterAIController::NotifyAbilityEnd()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsBool(TEXT("AbilityEnd"), true);
	}
}
