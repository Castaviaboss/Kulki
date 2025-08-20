// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseBoundaryActor.h"
#include "CA_BoundaryActor_Math_Push.generated.h"

class ACA_Character;

UCLASS()
class KULKI_API ACA_BoundaryActor_Math_Push : public ACA_BaseBoundaryActor
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

	UPROPERTY(EditAnywhere, Category = "Boundaries")
	float PushActivationDistance = 100.0f;
	
	UPROPERTY(EditAnywhere, Category = "Boundaries")
	float PushStrength = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Boundaries")
	bool bPushWithImpulse = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bShowDebugBounds = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (EditCondition = "bShowDebugBounds"))
	FColor DebugBoundaryColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (EditCondition = "bShowDebugBounds"))
	float DebugLineThickness = 2.0f;

private:

	TArray<FVector> Vertices;

	UPROPERTY()
	TObjectPtr<ACA_Character> Character;
	
	UPROPERTY()
	FVector ActualBoundaryMin = FVector::ZeroVector;

	UPROPERTY()
	FVector ActualBoundaryMax = FVector::ZeroVector;
};
