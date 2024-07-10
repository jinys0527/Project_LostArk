#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
public:
	GENERATED_USTRUCT_BODY()

	//생명력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CurrentLifePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float LifePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HPCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HP;

	//MP, AP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AP;

	//공격력 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Ability;

	//방어력 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DEFCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ArmorDEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Block;

	//회피, 명중률
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Dodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HitRate;

	
	//치명타 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalHitRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalDamageIncrease;

	//시너지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DamageIncrease;

	//경험치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float EXP;
};