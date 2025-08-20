// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CA_FindRandomPointToMove.generated.h"

UCLASS()
class KULKI_API UCA_FindRandomPointToMove : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCA_FindRandomPointToMove();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Radius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FBlackboardKeySelector TargetLocationKey;
};
