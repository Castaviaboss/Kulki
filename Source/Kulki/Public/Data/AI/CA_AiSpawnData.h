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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = "1", ClampMax = "100"))
	float ChanceToSpawn = 1.0f;
};

/**
 * DataAsset with enemyCharacter spawn settings
 *
 * With spawnConfiguration you can configure different types of enemies
 */
UCLASS()
class KULKI_API UCA_AiSpawnData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "If true – we will spawn enemies in the amount of CountMustBeSpawned. If false – enemies will spawn infinitely"))
	bool bUseSpawnCounter = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bUseSpawnCounter"))
	int32 CountMustBeSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D DelayBetweenSpawnRange = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "We can specify within the radius of which type of actor the enemies will spawn. Usually, this is CA_Character"))
	TSubclassOf<AActor> CenterOfSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D SpawnRadiusRange = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAiSpawnSetting> SpawnConfiguration;
};
