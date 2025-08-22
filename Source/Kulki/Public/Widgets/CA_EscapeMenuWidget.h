// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CA_EscapeMenuWidget.generated.h"

class ACA_GameState;
class ACA_PlayerController;

UCLASS()
class KULKI_API UCA_EscapeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	virtual void InitializeInputComponent() override;

protected:

	UFUNCTION(BlueprintCallable)
	void OnToggleWidget();

private:

	UPROPERTY()
	TObjectPtr<ACA_GameState> GameState;

	UPROPERTY()
	TObjectPtr<ACA_PlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<UGameViewportClient> GameViewportClient;
};
