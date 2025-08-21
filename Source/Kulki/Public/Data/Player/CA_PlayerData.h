// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_PlayerData.generated.h"

class UCA_EnemyStatsData;

UCLASS(Blueprintable)
class KULKI_API UCA_PlayerData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float StartStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	FVector2D AvailableStrengthRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float StartSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	FVector2D AvailableSpeedRange = FVector2D(1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float MassCoefficient = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats Settings")
	float AbsorptionFactor = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Settings")
	float CameraHeightFactor = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float MaxSpeed = 600.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float MaxForce = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
	float ForceMultiplier = 600.0f;
};
