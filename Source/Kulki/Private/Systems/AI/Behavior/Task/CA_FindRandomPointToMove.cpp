// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/AI/Behavior/Task/CA_FindRandomPointToMove.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UCA_FindRandomPointToMove::UCA_FindRandomPointToMove()
{
	NodeName = "Find Random Point";
}

EBTNodeResult::Type UCA_FindRandomPointToMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Controller invalid"), __FUNCTION__);
		return EBTNodeResult::Failed;;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Blackboard invalid"), __FUNCTION__);
		return EBTNodeResult::Failed;;
	}
	
	APawn* Pawn = Controller->GetPawn();
	if (!IsValid(Blackboard))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Pawn invalid"), __FUNCTION__);
		return EBTNodeResult::Failed;;
	}
	
	const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!IsValid(Blackboard))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] NavigationSystem invalid"), __FUNCTION__);
		return EBTNodeResult::Failed;;
	}
	
	FNavLocation NavLocation;
	const bool FoundLocation = NavigationSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
	if(!FoundLocation)
	{
		return EBTNodeResult::Failed;
	}
	
	Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
