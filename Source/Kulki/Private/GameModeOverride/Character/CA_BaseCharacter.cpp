// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeOverride/Character/CA_BaseCharacter.h"

DEFINE_LOG_CATEGORY(CharacterLog);

ACA_BaseCharacter::ACA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACA_BaseCharacter::ApplyStartStats(
	const float StartStrength,
	const float StartSpeed,
	const float BaseMassCoefficient)
{
	CurrentStrength = StartStrength;
	CurrentSpeed = StartSpeed;
	MassCoefficient = BaseMassCoefficient;
}

void ACA_BaseCharacter::AddStrength(
	const float StrengthToAdd,
	const float StrengthModifier)
{
	CurrentStrength += StrengthToAdd * StrengthModifier;
	CurrentStrength = FMath::Clamp(CurrentStrength, StrengthClamp.X, StrengthClamp.Y);

	ReduceSpeed(StrengthToAdd, MassCoefficient);
	
	UpdateStrengthModification();
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::AddSpeed(
	const float SpeedToAdd,
	const float SpeedModifier)
{
	CurrentSpeed += SpeedToAdd * SpeedModifier;
	CurrentSpeed = FMath::Clamp(CurrentSpeed, SpeedClamp.X, SpeedClamp.Y);
	
	UpdateSpeedModification();
	
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

void ACA_BaseCharacter::ReduceStrength(
	const float StrengthToReduce,
	const float StrengthModifier)
{
	CurrentStrength -= StrengthToReduce * StrengthModifier;
	CurrentStrength = FMath::Clamp(CurrentStrength, StrengthClamp.X, StrengthClamp.Y);

	AddSpeed(StrengthToReduce, MassCoefficient);

	UpdateStrengthModification();
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::ReduceSpeed(
	const float SpeedToReduce,
	const float SpeedModifier)
{
	CurrentSpeed -= SpeedToReduce * SpeedModifier;
	CurrentSpeed = FMath::Clamp(CurrentSpeed, SpeedClamp.X, SpeedClamp.Y);

	UpdateSpeedModification();
	
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

