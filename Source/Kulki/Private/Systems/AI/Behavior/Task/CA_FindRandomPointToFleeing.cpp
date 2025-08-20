// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AI/Behavior/Task/CA_FindRandomPointToFleeing.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

UCA_FindRandomPointToFleeing::UCA_FindRandomPointToFleeing()
{
	NodeName = "Find Point To Fleeing";
}

EBTNodeResult::Type UCA_FindRandomPointToFleeing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    if (!IsValid(Controller))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] Controller invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }

    const APawn* Pawn = Controller->GetPawn();
    if (!IsValid(Pawn))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] Pawn invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }

    const UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(Pawn->GetRootComponent());
    if (!IsValid(CapsuleComponent))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] CapsuleComponent invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }
    
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!IsValid(BlackboardComp))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] BlackboardComponent invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }

    const AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));
    if (!IsValid(PlayerActor))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] PlayerActor invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }

    const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!IsValid(NavigationSystem))
    {
        UE_LOG(LogTemp, Error, TEXT("[%hs] NavigationSystem invalid"), __FUNCTION__);
        return EBTNodeResult::Failed;
    }
    
    const FVector AILocation = Pawn->GetActorLocation();
    const FVector PlayerLocation = PlayerActor->GetActorLocation();

    FNavLocation SafeLocation;
    
    const FVector FleeDirection = (AILocation - PlayerLocation).GetSafeNormal2D();
    
    const float AngleOffset = FMath::FRandRange(RandomAngleRange.X, RandomAngleRange.Y);
    const FVector DesiredDir = FleeDirection.RotateAngleAxis(AngleOffset, FVector::UpVector);

    const FVector DesiredPoint = AILocation + DesiredDir * MaxFleeDistance;

    const bool bFound = NavigationSystem->ProjectPointToNavigation(
        DesiredPoint,
        SafeLocation,
        Extent);
    
    if (!bFound || FVector::Dist2D(SafeLocation.Location, PlayerLocation) < MinSafeDistance)
    {
        NavigationSystem->GetRandomReachablePointInRadius(AILocation, MaxFleeDistance, SafeLocation);
    }
    
    BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, SafeLocation.Location);

    return EBTNodeResult::Succeeded;
}


