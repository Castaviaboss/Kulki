// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CA_GameState.generated.h"

class UCA_BaseProcessor;
class ACA_EnemySpawner;
class ACA_ProcessorTickManager;
class UCA_LevelManagerComponent;

DECLARE_LOG_CATEGORY_EXTERN(GameStateLog, Log, All);

UCLASS()
class KULKI_API ACA_GameState : public AGameState
{
	GENERATED_BODY()

protected:

	ACA_GameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

public:

	void SetEnemySpawner(ACA_EnemySpawner* Spawner);

	UPROPERTY()
	TObjectPtr<ACA_ProcessorTickManager> TickManager;

private:

	UPROPERTY()
	TObjectPtr<UCA_LevelManagerComponent> LevelManager;

	UPROPERTY()
	TObjectPtr<ACA_EnemySpawner> EnemySpawner;
};
