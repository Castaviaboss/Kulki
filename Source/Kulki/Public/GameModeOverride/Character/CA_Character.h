// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseCharacter.h"
#include "CA_Character.generated.h"

class UCA_PlayerData;
class USpringArmComponent;
class UCameraComponent;
class UCA_HeroComponent;
class UCA_InputData;
class UInputMappingContext;
class ACA_PlayerController;

DECLARE_LOG_CATEGORY_EXTERN(CharacterLog, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyAbsorbed, EEnemyLeaderStats, AbsorbedEnemyType);

UCLASS()
class KULKI_API ACA_Character : public ACA_BaseCharacter
{
	GENERATED_BODY()

protected:
	
	ACA_Character();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	void SetMappingContext(const UInputMappingContext* MappingContext, const int32 Priority = 0) const;

//Movement
	
	FVector UpdateMousePosition() const;

	void MoveTowardsMouse(const float DeltaTime) const;

	void StartMove();

	void StopMove();

//Movement

public:

	UFUNCTION(BlueprintCallable)
	void PhysicalPushCharacter(
		const FVector& Force,
		const float PushStrength,
		const bool bImpulse = true);

	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

//Stats Calculating

	virtual void AddStrength(const float StrengthToAdd) override;

	virtual void ReduceStrength(const float StrengthToReduce) override;

//Stats Calculating

	void UpdateScaleFromStrength();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_PlayerController> PlayerController;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyAbsorbed OnEnemyAbsorbed;

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCA_PlayerData> PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxForce = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float ForceMultiplier = 600.0f;

private:

	bool bIsMoving = false;

	float InitialOrthoWidth;
	
	float InitialTargetArmLenght;

	float InitialScaleAverage;
};
