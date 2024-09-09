// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API ABossMonster : public AMonster
{
	GENERATED_BODY()
public:
	ABossMonster();

	TSubclassOf<ABossMonster> BossClass;

	static int32 BossWidgetCount;

	virtual void SetDead() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, Category = GAS)
	TSubclassOf<class UGameplayAbility> FireAbilityClass;

	void PlayFire();

	FORCEINLINE virtual class UAnimMontage* GetFireMontage() const { return FireMontage; }

	class UNiagaraComponent* Niagara;

	virtual void PlayHitReaction() override;

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
};
