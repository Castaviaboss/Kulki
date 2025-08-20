// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_AiGoalData.generated.h"

class UCA_BaseGoalProcessor;

UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Patrolling	UMETA(DisplayName = "Patrolling"),
	Chasing		UMETA(DisplayName = "Chasing"),
	Fleeing		UMETA(DisplayName = "Fleeing")
};

USTRUCT(BlueprintType)
struct FAiGoalConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyAIState AiStateType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_BaseGoalProcessor> GoalProcessor;
};

UCLASS()
class KULKI_API UCA_AiGoalData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAiGoalConfiguration> Goals;
};
