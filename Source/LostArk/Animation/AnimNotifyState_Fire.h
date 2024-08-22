// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h" 
#include "AnimNotifyState_Fire.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class LOSTARK_API UAnimNotifyState_Fire : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayCue")
	FGameplayTag GameplayCueTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> FireDamage;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> BurningDamage;*/

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	float ElapsedTime;
};
