// Fill out your copyright notice in the Description page of Project Settings.


#include "LostArkWidgetController.h"

void ULostArkWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void ULostArkWidgetController::BroadcastInitialValues()
{

}

void ULostArkWidgetController::BindCallbacksToDependencies()
{

}
