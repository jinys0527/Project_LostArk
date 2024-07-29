// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS_PlayerContext.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MyPlayer.h"

TArray<AActor*> UEQS_PlayerContext::GetPlayerContext()
{
	TArray<AActor*> PlayerContext;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayer::StaticClass(), PlayerContext);

	return PlayerContext;
}
