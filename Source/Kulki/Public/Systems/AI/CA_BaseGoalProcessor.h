// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CA_BaseGoalProcessor.generated.h"

class ACA_EnemyCharacter;
class ACA_AiController;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced, meta = (ShowWorldContextPin), Abstract)
class KULKI_API UCA_BaseGoalProcessor : public UObject
{
	GENERATED_BODY()

public:

	virtual void InitProcessor(
		ACA_AiController* OwnerController,
		ACA_EnemyCharacter* OwnerPawn);

	virtual void TickProcessor(
		const float DeltaSeconds);

protected:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Processor Init"))
	void K2_ProcessorInit(
		ACA_AiController* OwnerController,
		ACA_EnemyCharacter* OwnerPawn);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Tick Processor"))
	void K2_TickProcessor(
		const float DeltaSeconds);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPauseTick = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTick = false;

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_AiController> Controller;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_EnemyCharacter> Pawn;
};
