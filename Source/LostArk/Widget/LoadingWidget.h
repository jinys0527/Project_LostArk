// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API ULoadingWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
	ULoadingWidget();

	void Loading();

	void Loopback();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> SubLevelName;

	int32 LevelIndex = 0;

	bool bLoadComplete;

};
