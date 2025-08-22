// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Processors/CA_ProcessorTickManager.h"
#include "GameModeOverride/GameState/CA_GameState.h"
#include "Processors/CA_BaseProcessor.h"

ACA_ProcessorTickManager::ACA_ProcessorTickManager()
{
	PrimaryActorTick.bCanEverTick = true;
	AActor::SetActorTickEnabled(true);
}

void ACA_ProcessorTickManager::BeginPlay()
{
	Super::BeginPlay();

	ACA_GameState* GameState = Cast<ACA_GameState>(GetWorld()->GetGameState());
	if (!IsValid(GameState))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GameState invalid"), __FUNCTION__);
		return;
	}

	GameState->TickManager = this;
}

void ACA_ProcessorTickManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (UCA_BaseProcessor* Processor : GoalProcessors)
	{
		if (!IsValid(Processor))
		{
			UE_LOG(LogTemp, Error, TEXT("[%hs] Processor invalid"), __FUNCTION__);
			continue;
		}

		if (Processor->bPauseTick)
		{
			continue;
		}
		
		Processor->TickProcessor(DeltaSeconds);
	}
}

void ACA_ProcessorTickManager::AddProcessor(UCA_BaseProcessor* GoalProcessor)
{
	GoalProcessors.Add(GoalProcessor);
}

void ACA_ProcessorTickManager::RemoveProcessor(UCA_BaseProcessor* GoalProcessor)
{
	GoalProcessors.Remove(GoalProcessor);
}
