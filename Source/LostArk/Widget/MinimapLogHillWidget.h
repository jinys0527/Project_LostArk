// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "MinimapLogHillWidget.generated.h"

class UCanvasPanel;
class UCanvasPanelSlot;
class UMinimapPlayerWidget;
class UMinimapPortalWidget;
class UMinimapMonsterWidget;
class UMinimapNamedWidget;
class UMinimapBossWidget;
class AMonster;

/**
 * 
 */
UCLASS()
class LOSTARK_API UMinimapLogHillWidget : public ULostArkUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MiniMap")
    void UpdatePlayer(UMinimapPlayerWidget* PlayerWidget);

    UFUNCTION(BlueprintCallable, Category = "MiniMap")
    void UpdatePortal(UMinimapPortalWidget* PortalWidget);

    UFUNCTION(BlueprintCallable, Category = "MiniMap")
    void AddMonster(AMonster* Monster);

    UFUNCTION(BlueprintCallable, Category = "MiniMap")
    void UpdateMonster();

    UFUNCTION()
    void MonsterDead(AMonster* Monster);

    TArray<UUserWidget*> GetChildrenOfClass(UCanvasPanel* CanvasPanel, TSubclassOf<UUserWidget> WidgetClass);

protected:
    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* Map;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
    FVector2D MiniMapSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
    FVector2D WorldBoundsMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
    FVector2D WorldBoundsMax;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TSubclassOf<AActor> PortalClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TSubclassOf<UMinimapMonsterWidget> CommonWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TSubclassOf<UMinimapNamedWidget> NamedWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TSubclassOf<UMinimapBossWidget> BossWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TArray<UMinimapMonsterWidget*> MonsterWidget;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    TArray<UMinimapNamedWidget*> NamedWidget;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MiniMap")
    UMinimapBossWidget* BossWidget;

    FVector MonsterLocation;
    FVector2D MonsterMiniMapPosition;
    UCanvasPanelSlot* MonsterCanvasPanelSlot;

    int CommonCount = 0;
    int NamedCount = 0;

private:
    FVector2D ConvertWorldToMiniMap_Player(const FVector& WorldLocation) const;
    FVector2D ConvertWorldToMiniMap_Portal(const FVector& WorldLocation) const;
    FVector2D ConvertWorldToMiniMap_Monster(const FVector& WorldLocation) const;
    FVector2D ConvertWorldToMiniMap_Named(const FVector& WorldLocation) const;
    FVector2D ConvertWorldToMiniMap_Boss(const FVector& WorldLocation) const;
};
