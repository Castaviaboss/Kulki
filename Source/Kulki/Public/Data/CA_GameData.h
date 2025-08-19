// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_GameData.generated.h"

class UCA_InputData;

UCLASS()
class KULKI_API UCA_GameData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCA_InputData> InputData;
};
