// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Common/BaseCharacter.h"
#include "MyPlayer.generated.h"


class AGreatSword;

UCLASS(Blueprintable)
class AMyPlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMyPlayer();

	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	ECharacterState CurrentState;

	ECharacterState PrevState;

	void SetPlayerState(ECharacterState NewState);

	virtual void PlayDead() override;

	virtual void PlayHitReaction() override;

	void PlayResurrection();

	virtual void SetDead() override;

	UFUNCTION()
	virtual void OnOutOfHealth();

	UFUNCTION()
	virtual void OnGetDamage(AActor* DamageCauser, float Damage);

	void EquipSword();

	void UnEquipSword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AGreatSword> GreatSwordClass;

	void AttachSword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGreatSword* EquippedGreatSword;

	uint8 bIsEquipped : 1;

	uint8 bIsAttacking : 1;

	uint8 bIsAttack : 1;

	uint8 bIsCritical : 1;

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsInteractioned : 1;

	float DrawTimer;	//칼 빼는 시간을 위한 타이머

	FTimerHandle DrawHandle;

	void OnTimer();

	int32 TimeCount;

	FTimerHandle StepHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> EquipSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> UnEquipSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> ResurrectionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> HitReactionBattleMontage;

	FORCEINLINE virtual class UAnimMontage* GetEquipMontage() const { return EquipSwordMontage; }

	UPROPERTY(Transient)
	class UAnimInstance_Player* PlayerAnimInstance;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	TSet<AActor*> Target;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	class UAnimInstance_Player* AnimInstance;

	float GetPlayerLevel();

	void LevelUP();

	float GetPlayerExpeditionLevel();

	void ExpeditionLevelUP();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> InitEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> UpdateRequiredEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> UpdateExpeditionRequiredEXPEffectClass;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	virtual void InitAbilityActorInfo() override;
};