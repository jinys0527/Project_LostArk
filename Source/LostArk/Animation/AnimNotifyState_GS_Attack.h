// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayEffectTypes.h" 
#include "AnimNotifyState_GS_Attack.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UAnimNotifyState_GS_Attack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffect")
	TSubclassOf<class UGameplayEffect> EffectClass;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
};
