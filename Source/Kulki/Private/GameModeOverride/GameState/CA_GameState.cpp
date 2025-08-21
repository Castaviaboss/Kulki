// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/GameModeOverride/GameState/CA_GameState.h"

#include "GameModeOverride/Character/CA_BaseCharacter.h"
#include "Kulki/Public/Systems/LevelSystem/CA_LevelManagerComponent.h"
#include "Systems/AI/CA_BaseProcessor.h"

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

	if (!IsValid(GameStateProcessor))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] GameStateProcessor invalid"), __FUNCTION__);
		return;
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] PlayerController invalid"), __FUNCTION__);
		return;
	}

	ACA_BaseCharacter* Character = Cast<ACA_BaseCharacter>(PlayerController->GetPawn());
	if (!IsValid(PlayerController))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] Character invalid"), __FUNCTION__);
		return;
	}
	
	GameStateProcessor->InitProcessor(this, PlayerController, Character);
}

void ACA_GameState::SetEnemySpawner(ACA_EnemySpawner* Spawner)
{
	EnemySpawner = Spawner;
}
