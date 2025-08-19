// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseBoundaryActor.h"
#include "CA_BoundaryActor_Push.generated.h"

class ACA_Character;

UCLASS()
class KULKI_API ACA_BoundaryActor_Push : public ACA_BaseBoundaryActor
{
	GENERATED_BODY()

protected:

	virtual void InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig) override;

	UFUNCTION(BlueprintPure, Category = "Boundary Management")
	FVector CalculateBoundaryForce(const FVector& Position) const;
	
	UFUNCTION(BlueprintPure, Category = "Boundary Management")
	bool IsWithinBounds(const FVector& Position) const;
	
	UFUNCTION(BlueprintPure, Category = "Boundary Management")
	float GetDistanceToBoundary(const FVector& Position) const;
	
	virtual void Tick(float DeltaTime) override;

	void TrackCharacter() const;

private:
	
	void DrawDebugBoundaries();

protected:

	UPROPERTY(EditAnywhere)
	float PushActivationDistance = 100.0f;
	
	UPROPERTY(EditAnywhere)
	float PushStrength = 100.0f;

	UPROPERTY(EditAnywhere)
	bool bPushWithImpulse = true;

private:

	TArray<FVector> Vertices;

	UPROPERTY()
	TObjectPtr<ACA_Character> Character;
	
	UPROPERTY()
	FVector2D ActualBoundaryMin = FVector2D::ZeroVector;

	UPROPERTY()
	FVector2D ActualBoundaryMax = FVector2D::ZeroVector;
};
