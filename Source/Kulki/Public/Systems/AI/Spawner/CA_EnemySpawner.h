// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CA_EnemySpawner.generated.h"

struct FAiSpawnSetting;
class UNavigationSystemV1;
class UCA_AiSpawnData;

DECLARE_LOG_CATEGORY_EXTERN(SpawnerLog, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawned, int32, NewCount);

UCLASS()
class KULKI_API ACA_EnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	
	ACA_EnemySpawner();

protected:
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void StartSpawnTimer();

	UFUNCTION()
	void TrySpawnEnemy();

	FAiSpawnSetting GetSpawnSetting() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CountSpawnedEnemies = 0;

public:

	UPROPERTY(BlueprintAssignable)
	FOnEnemySpawned OnEnemySpawned;

private:

	UPROPERTY()
	TObjectPtr<UCA_AiSpawnData> SpawnData;

	UPROPERTY()
	TObjectPtr<AActor> CenterOfSpawn;

	UPROPERTY()
	TObjectPtr<UNavigationSystemV1> NavigationSystem;

	FTimerDelegate SpawnTimerDelegate;

	FTimerHandle SpawnTimerHandle;

	const float MinChanceToSpawn = 1.0f;

	const float MaxChanceToSpawn = 100.0f;

	const float DefaultBestOptionValue = -1.0f;
};
