// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/AI/EnemyPawn/CA_EnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Data/AI/CA_EnemyCharacterData.h"

ACA_EnemyCharacter::ACA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereDetector = CreateDefaultSubobject<USphereComponent>("SphereDetector");
	SphereDetector->SetupAttachment(RootComponent);
}

void ACA_EnemyCharacter::InitCharacter(
	UCA_EnemyCharacterData* Config,
	AActor* CenterOfSpawn)
{
	if (!IsValid(Config))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Config invalid"), __FUNCTION__);
		return;
	}
	
	if (Config->SourceFlipbook.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] SourceFlipbook null"), __FUNCTION__);
		return;
	}

	UPaperFlipbookComponent* FlipbookComponent = GetSprite();
	if (!IsValid(FlipbookComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] FlipbookComponent invalid"), __FUNCTION__);
		return;
	}

	UPaperFlipbook* Flipbook = Config->SourceFlipbook.LoadSynchronous();
	if (!IsValid(Flipbook))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Flipbook invalid"), __FUNCTION__);
		return;
	}
	
	FlipbookComponent->SetFlipbook(Flipbook);
	FlipbookComponent->SetSpriteColor(Config->SpriteColor);

	if (!IsValid(SphereDetector))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] SphereDetector invalid"), __FUNCTION__);
		return;
	}
	SphereDetector->SetSphereRadius(Config->SphereDetectorRadius);

	const UCA_EnemyStatsData* EnemyStats = Config->EnemyStats;
	if (!IsValid(EnemyStats))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] EnemyStats invalid"), __FUNCTION__);
		return;
	}

	const float StartStrength = FMath::RandRange(
		EnemyStats->Configuration.StartStrengthRange.X, EnemyStats->Configuration.StartStrengthRange.Y);

	const float StartSpeed = FMath::RandRange(
		EnemyStats->Configuration.StartSpeedRange.X, EnemyStats->Configuration.StartSpeedRange.Y);

	const float BaseMassCoefficient = FMath::RandRange(
		EnemyStats->Configuration.MassCoefficientRange.X, EnemyStats->Configuration.MassCoefficientRange.Y);

	LeaderStat = EnemyStats->Configuration.EnemyLeaderStat;
	
	SetActorScale3D(FVector(StartStrength));
	
	ApplyStartStats(StartStrength, StartSpeed, BaseMassCoefficient, 0);
}

bool ACA_EnemyCharacter::TryAbsorb(ACA_BaseCharacter* AbsorbInstigator)
{
	if (AbsorbInstigator->CurrentStrength > CurrentStrength)
	{
		switch (LeaderStat)
		{
			case EEnemyType::None: break;
			case EEnemyType::Red:
				AbsorbInstigator->AddStrength(CurrentStrength); break;
			case EEnemyType::Yellow:
				AbsorbInstigator->AddSpeed(CurrentSpeed); break;
			case EEnemyType::Purple:
				AbsorbInstigator->ReduceStrength(CurrentStrength);
				AbsorbInstigator->ReduceSpeed(CurrentSpeed); break;
		}
		Destroy();
		return true;
	}

	switch (LeaderStat)
	{
		case EEnemyType::None: break;
		case EEnemyType::Red:
			AbsorbInstigator->ReduceStrength(CurrentStrength); break;
		case EEnemyType::Yellow:
			AbsorbInstigator->ReduceSpeed(CurrentSpeed); break;
		case EEnemyType::Purple:
			AbsorbInstigator->ReduceStrength(CurrentStrength);
			AbsorbInstigator->ReduceSpeed(CurrentSpeed); break;
	}

	return false;
}

void ACA_EnemyCharacter::UpdateSpeed()
{
	Super::UpdateSpeed();

	
}
