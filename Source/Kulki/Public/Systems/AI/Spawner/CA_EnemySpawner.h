// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CA_EnemySpawner.generated.h"

UCLASS()
class KULKI_API ACA_EnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	
	ACA_EnemySpawner();

protected:
	
	virtual void BeginPlay() override;
};
