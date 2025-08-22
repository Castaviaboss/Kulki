// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CA_BaseCharacter.generated.h"

enum class EEnemyType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrengthChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyAbsorbed, EEnemyType, AbsorbedTargetType);

DECLARE_LOG_CATEGORY_EXTERN(CharacterLog, Log, All);

/**
 * Base ACA_BaseCharacter KULKI_API
 */

UCLASS()
class KULKI_API ACA_BaseCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	
	ACA_BaseCharacter();

//Stats Calculating

	void ApplyStartStats(
		const float StartStrength,
		const float StartSpeed,
		const float BaseMassCoefficient);

	UFUNCTION(BlueprintCallable)
	virtual void AddStrength(
		const float StrengthToAdd,
		const float StrengthModifier);

	UFUNCTION(BlueprintCallable)
	virtual void AddSpeed(
		const float SpeedToAdd,
		const float SpeedModifier);

	UFUNCTION(BlueprintCallable)
	virtual void ReduceStrength(
		const float StrengthToReduce,
		const float StrengthModifier);

	UFUNCTION(BlueprintCallable)
	virtual void ReduceSpeed(
		const float SpeedToReduce,
		const float SpeedModifier);
	
	virtual void UpdateStrengthModification() {}

	virtual void UpdateSpeedModification() {}

//Stats Calculating

	UPROPERTY(BlueprintAssignable)
	FOnEnemyAbsorbed OnTargetAbsorbed;

	UPROPERTY(BlueprintAssignable)
	FOnStrengthChanged OnStrengthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnSpeedChanged OnSpeedChanged;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentStrength = 0.0f;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentSpeed = 0.0f;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float MassCoefficient = 0.0f;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	FVector2D StrengthClamp = FVector2D::ZeroVector;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	FVector2D SpeedClamp = FVector2D::ZeroVector;
};
