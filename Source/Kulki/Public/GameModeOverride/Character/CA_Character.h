// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseCharacter.h"
#include "CA_Character.generated.h"

class ACA_EnemyCharacter;
class UCA_PlayerData;
class USpringArmComponent;
class UCameraComponent;
class UCA_HeroComponent;
class UCA_InputData;
class UInputMappingContext;
class ACA_PlayerController;

UCLASS()
class KULKI_API ACA_Character : public ACA_BaseCharacter
{
	GENERATED_BODY()

protected:
	
	ACA_Character();

//AActor
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

//AActor

//Input

	void SetMappingContext(const UInputMappingContext* MappingContext, const int32 Priority = 0) const;

//Input

//Movement
	
	FVector UpdateMousePosition() const;

	void MoveTowardsMouse(const float DeltaTime) const;

	void StartMove();

	void StopMove();

//Movement

public:

//Physic

	UFUNCTION(BlueprintCallable)
	void PhysicalPushCharacter(
		const FVector& Force,
		const float PushStrength,
		const bool bImpulse = true);
	
//Physic
	
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

	void AbsorbEnemy(const ACA_EnemyCharacter* Enemy);

	void PlayerAbsorbed(const ACA_EnemyCharacter* Enemy);

//Stats Calculating

	virtual void UpdateStrengthModification() override;

	virtual void UpdateSpeedModification() override;

//Stats Calculating

	void UpdateScaleFromStrength();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACA_PlayerController> PlayerController;

protected:

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UCA_PlayerData> PlayerData;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxForce = 0.0f;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category="Movement")
	float ForceMultiplier = 0.0f;

private:

	bool bIsMoving = false;

	float InitialOrthoWidth;
	
	float InitialTargetArmLenght;

	float InitialScaleAverage;

	bool ForceDestroyEnemyOnHit = false;

	float Axis3DCount = 3.0f;
};
