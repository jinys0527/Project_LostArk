// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LostArkUserWidget.h"
#include "MinimapTrixionWidget.generated.h"

class UMinimapPlayerWidget;
class UMinimapPortalWidget;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class LOSTARK_API UMinimapTrixionWidget : public ULostArkUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MiniMap")
	void UpdatePlayer(UMinimapPlayerWidget* PlayerWidget);

    UFUNCTION(BlueprintCallable, Category = "MiniMap")
    void UpdatePortal(UMinimapPortalWidget* PortalWidget);

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
    TSubclassOf<AActor> Portalclass;

private:
    FVector2D ConvertWorldToMiniMap(const FVector& WorldLocation) const;
};
