// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CA_PlayerController.generated.h"

UCLASS()
class KULKI_API ACA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetInputGameOnlyMode();
};
