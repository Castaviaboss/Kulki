// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_EnemyStatsData.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Red			UMETA(DisplayName = "Red"),
	Yellow		UMETA(DisplayName = "Yellow"),
	Purple		UMETA(DisplayName = "Purple")
};

USTRUCT(BlueprintType)
struct FEnemyStatsConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyType EnemyType = EEnemyType::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D StartStrengthRange = FVector2D(1.0f,1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D StartSpeedRange = FVector2D(1.0f,1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Determines the relationship between speed and strength: the greater the strength, the lower the speed, and vice versa"))
	FVector2D MassCoefficientRange = FVector2D(1.0f,1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "Range of the attribute modifier, calculated based on the SpawnRadiusRange in UCA_AiSpawnData. If an EnemyCharacter spawns at the minimum value of SpawnRadiusRange, it will receive the minimum modifier value accordingly. Used in the initial AI attribute calculations as a multiplier."))
	FVector2D SpawnRadiusMultiplierRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D ClampStrengthRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D ClampSpeedRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "A multiplier that determines the addition or subtraction of attributes to the player"))
	float AbsorptionCoefficient = 1.0f;
};

/**
 * DataAsset which contains enemyCharacter stats
 *
 * The range values are represented as a vector for more compact storage.
 */
UCLASS()
class KULKI_API UCA_EnemyStatsData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEnemyStatsConfiguration Configuration;
};
