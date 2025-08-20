// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CA_FindRandomPointToFleeing.generated.h"

class ACA_Character;

UCLASS()
class KULKI_API UCA_FindRandomPointToFleeing : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UCA_FindRandomPointToFleeing();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere)
	float MinSafeDistance = 300.f;

	UPROPERTY(EditAnywhere)
	float MaxFleeDistance = 800.f;

	UPROPERTY(EditAnywhere)
	FVector Extent = FVector(200.0f, 200.0f, 200.0f);

	UPROPERTY(EditAnywhere)
	FVector2D RandomAngleRange = FVector2D(-60.0f, 60.0f);
};
