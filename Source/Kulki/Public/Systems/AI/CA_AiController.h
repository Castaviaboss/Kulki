// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/DetourCrowdAIController.h"
#include "CA_AiController.generated.h"

UCLASS()
class KULKI_API ACA_AiController : public ADetourCrowdAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};
