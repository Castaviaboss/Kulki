// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kulki/Public/Data/Level/CA_LevelData.h"
#include "CA_BaseBoundaryActor.generated.h"

/**
 * A class that represents the boundaries of a map.
 * Boundaries can be implemented in different ways and have different shapes.
 */
UCLASS(Abstract)
class KULKI_API ACA_BaseBoundaryActor : public AActor
{
	GENERATED_BODY()

protected:

	ACA_BaseBoundaryActor();

public:

	UFUNCTION(BlueprintCallable, Category = "Boundary Management")
	virtual void InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig);

protected:

	UPROPERTY()
	FLevelBoundaryConfiguration BoundaryConfig = FLevelBoundaryConfiguration();
};
