// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/GameModeOverride/GameState/CA_GameState.h"
#include "Kulki/Public/Systems/LevelSystem/CA_LevelManagerComponent.h"

DEFINE_LOG_CATEGORY(GameStateLog);

ACA_GameState::ACA_GameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LevelManager = CreateDefaultSubobject<UCA_LevelManagerComponent>("LevelManager");
}

void ACA_GameState::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(LevelManager))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] LevelManager invalid"), __FUNCTION__);
		return;
	}
	LevelManager->InitManager();
}

void ACA_GameState::SetEnemySpawner(ACA_EnemySpawner* Spawner)
{
	EnemySpawner = Spawner;
}
