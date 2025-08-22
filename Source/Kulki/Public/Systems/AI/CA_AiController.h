// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AI/CA_AiGoalData.h"
#include "Runtime/AIModule/Classes/DetourCrowdAIController.h"
#include "CA_AiController.generated.h"

class ACA_EnemyCharacter;
enum class EEnemyAIState : uint8;
class UCA_AiGoalData;
class UCA_GoalProcessor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalUpdated);

UCLASS()
class KULKI_API ACA_AiController : public ADetourCrowdAIController
{
	GENERATED_BODY()

public:

	virtual void InitController(
		UCA_AiGoalData* GoalData,
		ACA_EnemyCharacter* OwnerPawn);
	
	UFUNCTION(BlueprintCallable)
	void UpdateGoal(
		const EEnemyAIState NewGoal,
		const UCA_GoalProcessor* GoalInstigator);

	UFUNCTION(BlueprintPure)
	EEnemyAIState& GetCurrentGoal() {return CurrentGoal;};

protected:

	UPROPERTY(BlueprintAssignable)
	FOnGoalUpdated OnGoalUpdated;

	UPROPERTY(Transient,VisibleAnywhere, BlueprintReadOnly)
	EEnemyAIState CurrentGoal = EEnemyAIState::None;

	UPROPERTY(Transient, EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(Transient, VisibleAnywhere)
	TArray<TObjectPtr<UCA_GoalProcessor>> ActiveProcessors;

private:

	const FName GoalKey = "GoalKey";
	
	const FName PlayerKey = "PlayerKey";
	
};
