// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayEffectTypes.h"
#include "AnimNotifyState_MonsterAttack.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UAnimNotifyState_MonsterAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	FActiveGameplayEffectHandle ActiveEffectHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffect")
	TSubclassOf<class UGameplayEffect> EffectClass;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
