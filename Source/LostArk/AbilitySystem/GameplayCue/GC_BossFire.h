// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_BossFire.generated.h"

class UNiagaraSystem;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class LOSTARK_API UGC_BossFire : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	UNiagaraSystem* FireNiagaraSystem;

	UGC_BossFire();

	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;

	AActor* Source;
};
