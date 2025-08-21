// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_GameStateData.generated.h"

class UCA_BaseProcessor;

UCLASS(Blueprintable)
class KULKI_API UCA_GameStateData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EnemiesCountMustBeAbsorbed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_BaseProcessor> GameStateProcessor;
};
