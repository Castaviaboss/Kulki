// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_PlayerData.generated.h"

class UCA_EnemyStatsData;

/**
 * DataAsset which contains player configuration. Stores everything related to player if that's need us in config
 */
UCLASS(Blueprintable)
class KULKI_API UCA_PlayerData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float StartStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	FVector2D ClampStrengthRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float StartSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	FVector2D ClampSpeedRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float MassCoefficient = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float MaxForce = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float ForceMultiplier = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float OrthoWidth = 512.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float TargetArmLenght = 512.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Settings")
	float CameraHeightFactor = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit Settings")
	bool ForceDestroyEnemyOnHit = false;
};
