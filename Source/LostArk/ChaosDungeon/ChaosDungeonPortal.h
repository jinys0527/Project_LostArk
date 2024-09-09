// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaosDungeonPortal.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class LOSTARK_API AChaosDungeonPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChaosDungeonPortal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TObjectPtr<UStaticMeshComponent> Portal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UWidgetComponent* MoveWidget;

	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	static int32 MoveWidgetCount;

	void LoadLevel(FName LevelName);

	UFUNCTION()
	void SetVisiblePortal();

	FTimerHandle InteractionCheckTimer;

	void CheckInteraction();

	class AMyPlayer* OverlappedPlayer;

	uint8 bIsOn : 1;

	void SavePlayerData(UGameInstance* GameInstance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
