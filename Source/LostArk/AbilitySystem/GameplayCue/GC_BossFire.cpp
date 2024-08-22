// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_BossFire.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../../Monster/BossMonster.h"

UGC_BossFire::UGC_BossFire()
{
}

bool UGC_BossFire::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const
{
	USkeletalMeshComponent* SkeletalMesh = Target->FindComponentByClass<USkeletalMeshComponent>();
	ABossMonster* Boss = Cast<ABossMonster>(Target);
	if (SkeletalMesh)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			FireNiagaraSystem,
			SkeletalMesh,
			FName("FireAttack"),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true
		);
		Boss->Niagara = NiagaraComp;
	}
	return false;
}
