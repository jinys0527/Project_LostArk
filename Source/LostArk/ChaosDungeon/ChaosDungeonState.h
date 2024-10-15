// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosDungeonState.generated.h"

UENUM(BlueprintType)
enum class EDungeonState : uint8
{
	None UMETA(DisplayName = "None"),
	Start UMETA(DisplayName = "Start"),
	Stage1 UMETA(DisplayName = "Stage1"),
	Stage2 UMETA(DisplayName = "Stage2"),
	Stage3 UMETA(DisplayName = "Stage3"),
	End UMETA(DisplayName = "End"),
	Fail UMETA(DisplayName = "Fail")
};