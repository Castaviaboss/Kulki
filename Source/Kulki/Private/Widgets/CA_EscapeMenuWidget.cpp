// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/CA_EscapeMenuWidget.h"

#include "CA_GameInstance.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Data/CA_GameData.h"
#include "Data/Input/CA_InputData.h"
#include "GameModeOverride/GameState/CA_GameState.h"
#include "GameModeOverride/PlayerController/CA_PlayerController.h"
#include "Kismet/GameplayStatics.h"

void UCA_EscapeMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameState = Cast<ACA_GameState>(GetWorld()->GetGameState());
	if (!IsValid(GameState))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GameState invalid"), __FUNCTION__);
		return;
	}

	PlayerController = Cast<ACA_PlayerController>(GetOwningPlayer());
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] PlayerController invalid"), __FUNCTION__);
		return;
	}

	GameViewportClient = GetWorld()->GetGameViewport();
	if (!IsValid(GameViewportClient))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GameViewportClient invalid"), __FUNCTION__);
		return;
	}

	InitializeInputComponent();
}

void UCA_EscapeMenuWidget::InitializeInputComponent()
{
	Super::InitializeInputComponent();

	const UCA_GameInstance* GameInstance = CastChecked<UCA_GameInstance>(GetGameInstance());

	const UCA_GameData* GameData = GameInstance->GameData;
	if (!IsValid(GameData))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GameData invalid"), __FUNCTION__);
		return;
	}

	const UCA_InputData* InputData = GameData->InputData;
	if (!IsValid(InputData))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] InputData invalid"), __FUNCTION__);
		return;
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		 EnhancedInputComponent->BindAction(GameData->InputData->EscapeAction,
			ETriggerEvent::Started, this, &UCA_EscapeMenuWidget::OnToggleWidget);
	}
}

void UCA_EscapeMenuWidget::OnToggleWidget()
{
	if (GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
	{
		PlayerController->SetInputGameOnlyMode();
		
		SetVisibility(ESlateVisibility::Hidden);

		if (!GameState->bGameEnded)
		{
			UGameplayStatics::SetGamePaused(PlayerController, false);
		}
	}
	else
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(GetCachedWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		
		UGameplayStatics::SetGamePaused(PlayerController, true);
	}
	
	GameViewportClient->SetIgnoreInput(false);
}
