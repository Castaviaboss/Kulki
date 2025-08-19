// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CA_Character.generated.h"

class UCA_InputData;
class UInputMappingContext;
class ACA_PlayerController;

DECLARE_LOG_CATEGORY_EXTERN(CharacterLog, Log, All);

UCLASS()
class KULKI_API ACA_Character : public APaperCharacter
{
	GENERATED_BODY()

protected:
	
	ACA_Character();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	void SetMappingContext(const UInputMappingContext* MappingContext, const int32 Priority = 0) const;

	FVector UpdateMousePosition() const;

	void MoveTowardsMouse(const float DeltaTime) const;

public:

	void PhysicalPushCharacter(
		const FVector& Force,
		const float PushStrength,
		const bool bImpulse = true) const;

protected:

	void StartMove();

	void StopMove();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_PlayerController> PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxForce = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float ForceMultiplier = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MinMouseDistanceForMove = 50.0f;

private:

	bool bIsMoving = false;
};
