// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CA_BaseProcessor.generated.h"

class ACA_BaseCharacter;
class ACA_AiController;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced, meta = (ShowWorldContextPin), Abstract)
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

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> InitInstigator;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AController> Controller;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_BaseCharacter> Pawn;
};
