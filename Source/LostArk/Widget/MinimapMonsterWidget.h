// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "MinimapMonsterWidget.generated.h"

class AMonster;

/**
 * 
 */
UCLASS()
class LOSTARK_API UMinimapMonsterWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	AMonster* Monster;
};
