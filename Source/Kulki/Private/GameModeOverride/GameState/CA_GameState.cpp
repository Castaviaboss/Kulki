// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/GameModeOverride/GameState/CA_GameState.h"

#include "CA_GameInstance.h"
#include "Data/CA_GameData.h"
#include "Data/GameState/CA_GameStateData.h"
#include "GameModeOverride/Character/CA_BaseCharacter.h"
#include "Kulki/Public/Systems/LevelSystem/CA_LevelManagerComponent.h"
#include "Systems/AI/CA_BaseProcessor.h"
#include "Systems/Processor/CA_GameStateProcessor.h"

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

	const UCA_GameInstance* GameInstance = CastChecked<UCA_GameInstance>(GetGameInstance());

	const UCA_GameData* GameData = GameInstance->GameData;
	if (!IsValid(GameData))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] GameData invalid"), __FUNCTION__);
		return;
	}

	const UCA_GameStateData* GameStateData = GameData->GameStateData;
	if (!IsValid(GameStateData))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] GameStateData invalid"), __FUNCTION__);
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

	if (GameStateData->GameStateProcessorClass.IsNull())
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] GameStateProcessorClass is null"), __FUNCTION__);
		return;
	}

	TSubclassOf<UCA_GameStateProcessor> ProcessorClass = GameStateData->GameStateProcessorClass.LoadSynchronous();
	if (!IsValid(ProcessorClass))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] ProcessorClass invalid"), __FUNCTION__);
		return;
	}

	UCA_GameStateProcessor* Processor = NewObject<UCA_GameStateProcessor>(this, ProcessorClass);
	if (!IsValid(Processor))
	{
		UE_LOG(GameStateLog, Error, TEXT("[%hs] Processor invalid"), __FUNCTION__);
		return;
	}
	
	Processor->InitProcessor(this, PlayerController, Character);
}

void ACA_GameState::SetEnemySpawner(ACA_EnemySpawner* Spawner)
{
	EnemySpawner = Spawner;
}
