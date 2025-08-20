// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/AI/CA_AiController.h"
#include "BehaviorTree/BehaviorTree.h"

void ACA_AiController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(BehaviorTree))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] BehaviorTree invalid"), __FUNCTION__);
		return;
	}

	RunBehaviorTree(BehaviorTree);
}
