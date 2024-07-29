// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQS_PlayerContext.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UEQS_PlayerContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	TArray<AActor*> GetPlayerContext();
};
