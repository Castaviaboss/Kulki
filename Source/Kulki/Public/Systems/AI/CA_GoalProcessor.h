// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseProcessor.h"
#include "CA_GoalProcessor.generated.h"

UCLASS()
class KULKI_API UCA_GoalProcessor : public UCA_BaseProcessor
{
	GENERATED_BODY()

public:

	void SetPriority(const int32 ProcessPriority);
	
	UPROPERTY(BlueprintReadOnly, Transient)
	int32 Priority = 0;
};
