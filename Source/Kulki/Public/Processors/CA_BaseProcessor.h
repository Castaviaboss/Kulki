// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CA_BaseProcessor.generated.h"

class ACA_BaseCharacter;
class ACA_AiController;

DECLARE_LOG_CATEGORY_EXTERN(ProcessorLog, Log, All);

/**
 * Simple UObject class, which mainly has to perform reactive logic.
 * Usually, this involves subscribing to an event during initialization and further processing the event internally.
 *
 * A separate tick is added, which is controlled by ACA_ProcessorTickManager.
 * Usually, there is no need for this, with rare exceptions.
 *
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin), Abstract)
class KULKI_API UCA_BaseProcessor : public UObject
{
	GENERATED_BODY()

public:

	virtual void InitProcessor(
		UObject* InstigatorInit,
		AController* OwnerController,
		ACA_BaseCharacter* OwnerPawn);

	virtual void TickProcessor(
		const float DeltaSeconds);

protected:

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Processor Init"))
	void K2_ProcessorInit(
		UObject* InstigatorInit,
		AController* OwnerController,
		ACA_BaseCharacter* OwnerPawn);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Tick Processor"))
	void K2_TickProcessor(
		const float DeltaSeconds);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPauseTick = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTick = false;

protected:

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UObject> InitInstigator;
	
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<AController> Controller;

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<ACA_BaseCharacter> Pawn;
};
