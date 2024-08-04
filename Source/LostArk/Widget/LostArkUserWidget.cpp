// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkUserWidget.h"

void ULostArkUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
