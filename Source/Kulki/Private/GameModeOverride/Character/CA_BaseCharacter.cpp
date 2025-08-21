// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeOverride/Character/CA_BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
	CurrentSpeed -= StrengthToAdd * MassCoefficient;
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::ReduceStrength(const float StrengthToReduce)
{
	CurrentStrength -= StrengthToReduce * AbsorptionFactor;
	CurrentSpeed += StrengthToReduce * MassCoefficient;
	
	if (OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(CurrentStrength);
	}
}

void ACA_BaseCharacter::AddSpeed(const float SpeedToAdd)
{
	CurrentSpeed += SpeedToAdd * AbsorptionFactor;
	CurrentSpeed = FMath::Min(CurrentSpeed, GetCharacterMovement()->GetMaxSpeed());

	UpdateSpeed();
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

void ACA_BaseCharacter::ReduceSpeed(const float SpeedToReduce)
{
	CurrentSpeed -= SpeedToReduce * AbsorptionFactor;
	CurrentSpeed = FMath::Max(CurrentSpeed, 0);

	UpdateSpeed();
	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast(CurrentSpeed);
	}
}

void ACA_BaseCharacter::UpdateSpeed()
{
	
}

