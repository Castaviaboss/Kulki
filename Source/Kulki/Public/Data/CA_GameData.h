// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_GameData.generated.h"

class UCA_GameStateData;
class UCA_PlayerData;
class UCA_AiSpawnData;
class UCA_LevelData;
class UCA_InputData;

/**
 * Very cool DataAsset, which contains all the necessary data that needs to be accessed during gameplay.
 * It is usually stored in the GameInstance for easy access and to ensure it exists at BeginPlay.
 */
UCLASS()
class KULKI_API UCA_GameData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_InputData> InputData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_LevelData> LevelData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_AiSpawnData> SpawnData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_PlayerData> PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_GameStateData> GameStateData;
};
