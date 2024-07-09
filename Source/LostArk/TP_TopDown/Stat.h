#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Dodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HitRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalHitRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalDamageIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DamageIncrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float EXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Ability;
};