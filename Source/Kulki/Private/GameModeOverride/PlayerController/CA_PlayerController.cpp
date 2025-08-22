// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/GameModeOverride/PlayerController/CA_PlayerController.h"

void ACA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);

	SetInputGameOnlyMode();
}

void ACA_PlayerController::SetInputGameOnlyMode()
{
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	SetInputMode(InputMode);
}
