// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_GameStateData.generated.h"

class UCA_GameStateProcessor;

/**
 * DataAsset which contains base rule for winning game
 *
 * Inside GameStateProcessorClass, the logic is implemented to track the win or lose conditions,
 * and when the conditions are met, it executes certain actions, such as pausing the game.
 */
UCLASS(Blueprintable)
class KULKI_API UCA_GameStateData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EnemiesCountMustBeAbsorbed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UCA_GameStateProcessor> GameStateProcessorClass;
};
