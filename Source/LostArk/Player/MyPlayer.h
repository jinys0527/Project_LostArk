// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Common/BaseCharacter.h"
#include "MyPlayer.generated.h"

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

	FStat Stat;

	ECharacterState CurrentState;

	ECharacterState PrevState;

	void SetPlayerState(ECharacterState NewState);

	virtual void PlayDead();

	virtual void PlayHitReaction() override;

	virtual void Attack() override;

	void PlayResurrection() ;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Resurrection();

	void EquipSword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSword> GreatSwordClass;

	void AttachSword();

	class AGreatSword* EquippedGreatSword;

	uint8 bIsEquipped : 1;

	uint8 bIsAttacking : 1;

	uint8 bIsAttack : 1;

	uint8 bIsCritical : 1;

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

	UPROPERTY(Transient)
	class UAnimInstance_Player* PlayerAnimInstance;

	TArray<AActor*> Target;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};