// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "MinimapBossWidget.generated.h"

class AMonster;

/**
 * 
 */
UCLASS()
class LOSTARK_API UMinimapBossWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	AMonster* Monster;
};
