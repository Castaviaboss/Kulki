// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/AI/CA_AiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Systems/AI/CA_BaseProcessor.h"
#include "Systems/AI/EnemyPawn/CA_EnemyCharacter.h"

void ACA_AiController::InitController(
	UCA_AiGoalData* GoalData,
	ACA_EnemyCharacter* OwnerPawn)
{
	if (!IsValid(BehaviorTree))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] BehaviorTree invalid"), __FUNCTION__);
		return;
	}

	RunBehaviorTree(BehaviorTree);

	for (const FAiGoalConfiguration& Configuration : GoalData->Goals)
	{
		if (!IsValid(Configuration.GoalProcessor))
		{
			UE_LOG(LogTemp, Warning, TEXT("[%hs] GoalProcessor invalid"), __FUNCTION__);
			continue;
		}

		Configuration.GoalProcessor->InitProcessor(this, this, OwnerPawn);
	}

	if (!IsValid(GetBlackboardComponent()))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GetBlackboardComponent invalid"), __FUNCTION__);
		return;
	}
	
	GetBlackboardComponent()->SetValueAsObject(PlayerKey, GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ACA_AiController::UpdateGoal(const EEnemyAIState NewGoal)
{
	CurrentGoal = NewGoal;
	
	if (!IsValid(GetBlackboardComponent()))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] GetBlackboardComponent invalid"), __FUNCTION__);
		return;
	}
	GetBlackboardComponent()->SetValueAsEnum(GoalKey, static_cast<uint8>(NewGoal));

	if (OnGoalUpdated.IsBound())
	{
		OnGoalUpdated.Broadcast();
	}
}
