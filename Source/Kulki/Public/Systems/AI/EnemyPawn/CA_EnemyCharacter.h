// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CA_EnemyStatsData.h"
#include "GameModeOverride/Character/CA_BaseCharacter.h"
#include "CA_EnemyCharacter.generated.h"

enum class EEnemyType : uint8;
class UCA_HeroComponent;
class UCA_EnemyCharacterData;
class USphereComponent;

UCLASS()
class KULKI_API ACA_EnemyCharacter : public ACA_BaseCharacter
{
	GENERATED_BODY()

public:

	ACA_EnemyCharacter();

	virtual void InitCharacter(
		UCA_EnemyCharacterData* Config,
		const float SpawnRadiusMultiplier);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereDetector;

	UPROPERTY(Transient,BlueprintReadOnly)
	EEnemyType EnemyType = EEnemyType::Red;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float AbsorptionCoefficient = 0.0f;
};
