// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
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

	virtual void PlayDead();

	virtual void PlayHitReaction();

	virtual void Move();

	virtual void Attack();

	virtual void PlayResurrection();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Resurrection();

	void EquipSword();

	void UnEquipSword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AGreatSword> GreatSwordClass;

	void AttachSword();

	class AGreatSword* EquippedGreatSword;

	uint8 bIsEquipped : 1;

	float StepTimer; //장착시 타이머 시작 -> 공격 안들어가는 순간마다 타이머를 재고 일정 시간뒤에 장착 해제

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> EquipSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> UnEquipSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> ResurrectionMontage;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

