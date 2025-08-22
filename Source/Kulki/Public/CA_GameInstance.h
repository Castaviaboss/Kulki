// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CA_GameInstance.generated.h"

class UCA_GameData;


/**
 * Base GameInstance KULKI_API
 */
UCLASS()
class KULKI_API UCA_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCA_GameData> GameData;
};
