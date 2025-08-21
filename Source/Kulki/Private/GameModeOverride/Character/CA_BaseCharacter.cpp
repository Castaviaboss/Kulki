// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeOverride/Character/CA_BaseCharacter.h"

ACA_BaseCharacter::ACA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACA_BaseCharacter::ApplyStartStats(
	const float StartStrength,
	const float StartSpeed,
	const float BaseMassCoefficient,
	const float BaseAbsorptionFactor)
{
	CurrentStrength = StartStrength;
	CurrentSpeed = StartSpeed;
	MassCoefficient = BaseMassCoefficient;
	AbsorptionFactor = BaseAbsorptionFactor;

	UpdateSpeed();
}

void ACA_BaseCharacter::AddStrength(const float StrengthToAdd)
{
	CurrentStrength += StrengthToAdd * AbsorptionFactor;
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::ReduceStrength(const float StrengthToReduce)
{
	CurrentStrength -= StrengthToReduce * AbsorptionFactor;
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::AddSpeed(const float SpeedToAdd)
{
	const float Gain = SpeedToAdd / AbsorptionFactor;
	const float Penalty = CurrentStrength * MassCoefficient;

	CurrentSpeed += Gain - Penalty;

	UpdateSpeed();
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

void ACA_BaseCharacter::ReduceSpeed(const float SpeedToReduce)
{
	const float Loss = SpeedToReduce * AbsorptionFactor;
	const float Penalty = CurrentStrength * MassCoefficient;

	CurrentSpeed -= (Loss + Penalty);

	UpdateSpeed();
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

void ACA_BaseCharacter::UpdateSpeed()
{
	
}

