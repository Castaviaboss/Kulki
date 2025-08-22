// Fill out your copyright notice in the Description page of Project Settings.

#include "Processors/CA_BaseProcessor.h"
#include "GameModeOverride/GameState/CA_GameState.h"
#include "Processors/CA_ProcessorTickManager.h"

DEFINE_LOG_CATEGORY(ProcessorLog)

void UCA_BaseProcessor::InitProcessor(
	UObject* InstigatorInit,
	AController* OwnerController,
	ACA_BaseCharacter* OwnerPawn)
{
	InitInstigator = InstigatorInit;
	Controller = OwnerController;
	Pawn = OwnerPawn;

	if (bTick)
	{
		const ACA_GameState* GameState = Cast<ACA_GameState>(Controller->GetWorld()->GetGameState());
		if (!IsValid(GameState))
		{
			UE_LOG(ProcessorLog, Error, TEXT("[%hs] GameState invalid"), __FUNCTION__);
			return;
		}
		ACA_ProcessorTickManager* TickManager = GameState->TickManager;
		if (!IsValid(TickManager))
		{
			UE_LOG(ProcessorLog, Error, TEXT("[%hs] TickManager invalid"), __FUNCTION__);
			return;
		}
		TickManager->AddProcessor(this);
	}
	
	K2_ProcessorInit(InitInstigator, OwnerController, OwnerPawn);
}

void UCA_BaseProcessor::TickProcessor(const float DeltaSeconds)
{
	K2_TickProcessor(DeltaSeconds);
}
