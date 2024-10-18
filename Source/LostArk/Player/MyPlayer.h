// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Common/BaseCharacter.h"
#include "MyPlayer.generated.h"

class AGreatSword;
class AMonster;
class UAttributeSet;
class UNiagaraSystem;
class UNiagaraComponent;
class UChaosDungeonGameInstance;

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

	void AttachSword();
	
	float DrawTimer;	//칼 빼는 시간을 위한 타이머

	void OnTimer();

	FORCEINLINE virtual class UAnimMontage* GetEquipMontage() const { return EquipSwordMontage; }
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	float GetPlayerLevel();

	void LevelUP();

	float GetPlayerExpeditionLevel();

	void ExpeditionLevelUP();

	virtual void InitAbilityActorInfo() override;

	void MaintainStatus(UChaosDungeonGameInstance* GameInstance);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AGreatSword> GreatSwordClass;

	ECharacterState CurrentState;

	ECharacterState PrevState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGreatSword* EquippedGreatSword;

	uint8 bIsEquipped : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bIsAttack : 1; 

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsInteractioned : 1;

	FTimerHandle DrawHandle;

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

	UPROPERTY(Transient)
	class UAnimInstance_Player* PlayerAnimInstance;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	TSet<AMonster*> Target;

	TSet<AMonster*> TargetDestroy;

	class UAnimInstance_Player* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> InitEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> UpdateRequiredEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> UpdateExpeditionRequiredEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> MaintainEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> MaintainRequiredEXPEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> MaintainStatusEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> MaintainMaxLifePointEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> MaintainCurrentLMEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LevelUP)
	UNiagaraSystem* LevelUPNiagara;

	FTimerHandle LevelUpTimerHandle;

	UNiagaraComponent* NiagaraComp;
};