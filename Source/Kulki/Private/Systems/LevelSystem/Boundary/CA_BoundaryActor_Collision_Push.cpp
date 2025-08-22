// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/LevelSystem/Boundary/CA_BoundaryActor_Collision_Push.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameModeOverride/Character/CA_Character.h"

ACA_BoundaryActor_Collision_Push::ACA_BoundaryActor_Collision_Push()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACA_BoundaryActor_Collision_Push::InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig)
{
	Super::InitBoundary(InBoundaryConfig);
	
	PrimitiveComponent = GetComponentByClass<UPrimitiveComponent>();
	if (!IsValid(PrimitiveComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] PrimitiveComponent invalid"), __FUNCTION__);
		return;
	}

	if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(PrimitiveComponent))
	{
		FVector Extent;
		Extent.X = (InBoundaryConfig.BoxMax.X - InBoundaryConfig.BoxMin.X) * HalfExtend;
		Extent.Y = (InBoundaryConfig.BoxMax.Y - InBoundaryConfig.BoxMin.Y) * HalfExtend;
		Extent.Z = (InBoundaryConfig.BoxMax.Z - InBoundaryConfig.BoxMin.Z) * HalfExtend;
		
		BoxComponent->SetBoxExtent(Extent);
	}
	else if (USphereComponent* SphereComponent = Cast<USphereComponent>(PrimitiveComponent))
	{
		SphereComponent->SetSphereRadius(InBoundaryConfig.SphereRadius);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Logic of selected primitive component is not implemented"), __FUNCTION__);
	}
}

void ACA_BoundaryActor_Collision_Push::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (!IsValid(PrimitiveComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] PrimitiveComponent invalid"), __FUNCTION__);
		return;
	}

	ACA_Character* Character = Cast<ACA_Character>(OtherActor);
	if (!IsValid(Character))
	{
		return;
	}

	const FVector CharacterLocation = Character->GetActorLocation();
	FVector ClosestPoint;
	PrimitiveComponent->GetClosestPointOnCollision(CharacterLocation, ClosestPoint);
	
	if (!ClosestPoint.IsNearlyZero())
	{
		const FVector PushDirection = ClosestPoint - CharacterLocation;
		Character->PhysicalPushCharacter(
			PushDirection,
			PushStrength,
			bPushWithImpulse
		);
	}
}


