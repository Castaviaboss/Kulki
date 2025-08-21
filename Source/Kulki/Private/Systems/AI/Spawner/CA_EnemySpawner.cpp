// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/AI/Spawner/CA_EnemySpawner.h"

#include "CA_GameInstance.h"
#include "NavigationSystem.h"
#include "Algo/RandomShuffle.h"
#include "Data/CA_GameData.h"
#include "Data/AI/CA_AiSpawnData.h"
#include "Data/AI/CA_EnemyCharacterData.h"
#include "GameModeOverride/GameState/CA_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/AI/CA_AiController.h"
#include "Systems/AI/EnemyPawn/CA_EnemyCharacter.h"

DEFINE_LOG_CATEGORY(SpawnerLog);

ACA_EnemySpawner::ACA_EnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACA_EnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] World invalid"), __FUNCTION__);
		return;
	}

	const UCA_GameInstance* GameInstance = CastChecked<UCA_GameInstance>(World->GetGameInstance());

	ACA_GameState* GameState = Cast<ACA_GameState>(World->GetGameState());
	if (!IsValid(GameState))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] GameState invalid"), __FUNCTION__);
		return;
	}
	GameState->SetEnemySpawner(this);

	const UCA_GameData* GameData = GameInstance->GameData;
	if (!IsValid(GameData))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] GameData invalid"), __FUNCTION__);
		return;
	}

	SpawnData = GameData->SpawnData;
	if (!IsValid(SpawnData))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] SpawnData invalid"), __FUNCTION__);
		return;
	}
	
	CenterOfSpawn = UGameplayStatics::GetActorOfClass(World, SpawnData->CenterOfSpawn);
	if (!IsValid(CenterOfSpawn))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] CenterOfSpawn invalid"), __FUNCTION__);
		return;
	}

	NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!IsValid(NavigationSystem))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] NavigationSystem invalid"), __FUNCTION__);
		return;
	}

	SpawnTimerDelegate.BindUObject(this, &ACA_EnemySpawner::TrySpawnEnemy);

	StartSpawnTimer();
}

void ACA_EnemySpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SpawnTimerDelegate.Unbind();
	
	Super::EndPlay(EndPlayReason);
}

void ACA_EnemySpawner::StartSpawnTimer()
{
	const float DelayFirstSpawn = FMath::RandRange(
		SpawnData->DelayBetweenSpawnRange.X, SpawnData->DelayBetweenSpawnRange.Y);
	
	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		SpawnTimerDelegate,
		DelayFirstSpawn,
		false);
}

void ACA_EnemySpawner::TrySpawnEnemy()
{
	if (!IsValid(CenterOfSpawn))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] CenterOfSpawn invalid"), __FUNCTION__);
		return;
	}

	if (!IsValid(SpawnData))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] SpawnData invalid"), __FUNCTION__);
		return;
	}

	if (!IsValid(NavigationSystem))
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] NavigationSystem invalid"), __FUNCTION__);
		return;
	}

	const FAiSpawnSetting SelectedSetting = GetSpawnSetting();
	if (SelectedSetting.EnemyClass.IsNull())
	{
		UE_LOG(SpawnerLog, Error, TEXT("[%hs] EnemyClass is null"), __FUNCTION__);
		return;
	}

	FVector Center = CenterOfSpawn->GetActorLocation();
	float Distance = FMath::FRandRange(SpawnData->SpawnRadiusRange.X, SpawnData->SpawnRadiusRange.Y);
	
	float Angle = FMath::FRandRange(0.f, 2.f * PI);
	
	FVector Offset = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * Distance;
	FVector CandidateLocation = Center + Offset;
	
	FNavLocation NavLocation;
	if (NavigationSystem->ProjectPointToNavigation(CandidateLocation, NavLocation))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACA_EnemyCharacter* Enemy = GetWorld()->SpawnActor<ACA_EnemyCharacter>(
			SelectedSetting.EnemyClass.LoadSynchronous(),
			NavLocation.Location,
			FRotator::ZeroRotator,
			SpawnParams
		);
		if (!IsValid(Enemy))
		{
			StartSpawnTimer();
			return;
		}

		float RadiusMultiplier = FMath::GetMappedRangeValueClamped(
	SpawnData->SpawnRadiusRange,
	SelectedSetting.CharacterData->EnemyStats->Configuration.SpawnRadiusMultiplierRange,
			Distance
		);
		
		Enemy->InitCharacter(SelectedSetting.CharacterData, RadiusMultiplier);

		if (!Enemy->GetController())
		{
			Enemy->SpawnDefaultController();
		}

		ACA_AiController* AiController = Cast<ACA_AiController>(Enemy->GetController());
		if (!IsValid(AiController))
		{
			UE_LOG(SpawnerLog, Error, TEXT("[%hs] AiController invalid"), __FUNCTION__);
			return;
		}
		AiController->InitController(SelectedSetting.EnemyGoal, Enemy);

		if (SpawnData->bUseSpawnCounter)
		{
			CountSpawnedEnemies++;
		}

		if (OnEnemySpawned.IsBound())
		{
			OnEnemySpawned.Broadcast(CountSpawnedEnemies);
		}
	}
	else
	{
		UE_LOG(SpawnerLog, Warning, TEXT("[%hs] Failed spawn enemy"), __FUNCTION__);
	}

	if (CountSpawnedEnemies >= SpawnData->CountMustBeSpawned)
	{
		return;
	}
	
	StartSpawnTimer();
}

FAiSpawnSetting ACA_EnemySpawner::GetSpawnSetting() const
{
	if (!SpawnData || SpawnData->SpawnConfiguration.Num() == 0)
	{
		return FAiSpawnSetting();
	}
	
	float TotalWeight = 0.0f;
	for (const FAiSpawnSetting& Setting : SpawnData->SpawnConfiguration)
	{
		TotalWeight += Setting.ChanceToSpawn;
	}
	
	float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
	
	for (const FAiSpawnSetting& Setting : SpawnData->SpawnConfiguration)
	{
		if (RandomValue < Setting.ChanceToSpawn)
		{
			return Setting;
		}
		RandomValue -= Setting.ChanceToSpawn;
	}

	return SpawnData->SpawnConfiguration.Last();
}

