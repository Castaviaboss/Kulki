// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_AiSpawnData.generated.h"

class UCA_EnemyCharacterData;
class UCA_AiGoalData;
class ACA_EnemyCharacter;

USTRUCT(BlueprintType)
struct FAiSpawnSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ACA_EnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_AiGoalData> EnemyGoal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_EnemyCharacterData> CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(UIMin = "1", ClampMin = "1", UIMax = "100", ClampMax = "100"))
	float ChanceToSpawn = 1.0f;
};

UCLASS()
class KULKI_API UCA_AiSpawnData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseSpawnCounter = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bUseSpawnCounter"))
	int32 CountMustBeSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D DelayBetweenSpawnRange = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> CenterOfSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D SpawnRadiusRange = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAiSpawnSetting> SpawnConfiguration;
};
