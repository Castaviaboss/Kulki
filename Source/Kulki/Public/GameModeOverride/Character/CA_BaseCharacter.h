// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CA_BaseCharacter.generated.h"

enum class EEnemyType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrengthChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChanged, float, NewValue);

UCLASS()
class KULKI_API ACA_BaseCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	
	ACA_BaseCharacter();

protected:

	void ApplyStartStats(
		const float StartStrength,
		const float StartSpeed,
		const float BaseMassCoefficient,
		const float BaseAbsorptionFactor);

public:

	virtual bool TryAbsorb(ACA_BaseCharacter* AbsorbInstigator) { return true; }

	//Stats Calculating

	UFUNCTION(BlueprintCallable)
	virtual void AddStrength(const float StrengthToAdd);

	UFUNCTION(BlueprintCallable)
	virtual void AddSpeed(const float SpeedToAdd);

	UFUNCTION(BlueprintCallable)
	virtual void ReduceStrength(const float StrengthToReduce);

	UFUNCTION(BlueprintCallable)
	virtual void ReduceSpeed(const float SpeedToReduce);

	//Stats Calculating

	virtual void UpdateSpeed();

	UPROPERTY(BlueprintAssignable)
	FOnStrengthChanged OnStrengthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnSpeedChanged OnSpeedChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentStrength = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float MassCoefficient = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float AbsorptionFactor = 1.0f;
};
