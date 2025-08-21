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
	EEnemyType EnemyLeaderStat = EEnemyType::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D StartStrengthRange = FVector2D(1.0f,1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D StartSpeedRange = FVector2D(1.0f,1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D MassCoefficientRange = FVector2D(1.0f,1.0f);
};

UCLASS()
class KULKI_API UCA_EnemyStatsData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEnemyStatsConfiguration Configuration;
};
