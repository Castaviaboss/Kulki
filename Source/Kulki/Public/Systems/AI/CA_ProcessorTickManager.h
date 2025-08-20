// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_ProcessorTickManager.generated.h"

class UCA_BaseGoalProcessor;

UCLASS()
class KULKI_API ACA_ProcessorTickManager : public AActor
{
	GENERATED_BODY()

public:
	
	ACA_ProcessorTickManager();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	void AddProcessor(UCA_BaseGoalProcessor* GoalProcessor);

	void RemoveProcessor(UCA_BaseGoalProcessor* GoalProcessor);

private:

	UPROPERTY()
	TArray<TObjectPtr<UCA_BaseGoalProcessor>> GoalProcessors;
};
