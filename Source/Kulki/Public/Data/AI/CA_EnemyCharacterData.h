// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "Engine/DataAsset.h"
#include "CA_EnemyCharacterData.generated.h"

UCLASS()
class KULKI_API UCA_EnemyCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UPaperFlipbook> SourceFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SpriteColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SphereDetectorRadius = 256.0f;
};
