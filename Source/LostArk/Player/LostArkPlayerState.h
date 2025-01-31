// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "LostArkPlayerState.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class LOSTARK_API ALostArkPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALostArkPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetAttributeSet(UAttributeSet* NewAttributeSet);

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE float GetPlayerLevel() { return Level; }

	FORCEINLINE float GetPlayerExpeditionLevel() { return ExpeditionLevel; }

	void SetPlayerLevel(float NewLevel);

	void SetPlayerExpeditionLevel(float NewExpeditionLevel);

	FORCEINLINE void LevelUP() { Level++; }

	FORCEINLINE void ExpeditionLevelUP() { ExpeditionLevel++; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Feathers;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	float Level = 1.0f;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_ExpeditionLevel)
	float ExpeditionLevel = 1.0f;

	UFUNCTION()
	void OnRep_Level();

	UFUNCTION()
	void OnRep_ExpeditionLevel ();
};
