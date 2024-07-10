#pragma once

#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
public:
	GENERATED_USTRUCT_BODY()

	//�����
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

	//���ݷ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float WeaponATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Ability;

	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DEFCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float ArmorDEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Block;

	//ȸ��, ���߷�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Dodge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HitRate;

	
	//ġ��Ÿ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalHitRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float CriticalDamageIncrease;

	//�ó���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DamageIncrease;

	//����ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float EXP;
};