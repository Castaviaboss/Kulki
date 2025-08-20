// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CA_BaseBoundaryActor.h"
#include "CA_BoundaryActor_Collision_Push.generated.h"

class ACA_Character;

UCLASS()
class KULKI_API ACA_BoundaryActor_Collision_Push : public ACA_BaseBoundaryActor
{
	GENERATED_BODY()

public:
	
	ACA_BoundaryActor_Collision_Push();

protected:
	
	virtual void InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Boundaries")
	float PushStrength = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Boundaries")
	bool bPushWithImpulse = true;

private:

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> PrimitiveComponent;
};
