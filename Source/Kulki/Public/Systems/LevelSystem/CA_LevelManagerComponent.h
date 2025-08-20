// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CA_LevelManagerComponent.generated.h"

class ACA_BaseBoundaryActor;
class UCA_LevelData;
class APaperSpriteActor;

DECLARE_LOG_CATEGORY_EXTERN(LevelManagerLog, Log, All);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KULKI_API UCA_LevelManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UCA_LevelManagerComponent();

public:

	void InitManager();

protected:

	void SetupPlane(const UCA_LevelData* LevelData, UWorld* World);

	void SetupBoundary(const UCA_LevelData* LevelData, UWorld* World);

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APaperSpriteActor> PlaneActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_BaseBoundaryActor> BoundaryActor;

private:

	const int8 DefaultMaterialIndex = 0;
};
