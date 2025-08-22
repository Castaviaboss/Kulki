// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "Engine/DataAsset.h"
#include "CA_EnemyCharacterData.generated.h"

class UCA_EnemyStatsData;

/**
 * DataAsset which contains visual attributes for EnemyCharacter and stats
 */
UCLASS()
class KULKI_API UCA_EnemyCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_EnemyStatsData> EnemyStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UPaperFlipbook> SourceFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SpriteColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ToolTip = "The AI has a sphere responsible for detecting the player. It is used in AI tasks that involve reacting to the player’s approach or retreat"))
	float SphereDetectorRadius = 256.0f;
};
