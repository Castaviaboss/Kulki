// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/LevelSystem/Boundary/CA_BoundaryActor_Math_Push.h"
#include "Kulki/Public/GameModeOverride/Character/CA_Character.h"

void ACA_BoundaryActor_Math_Push::InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig)
{
	Super::InitBoundary(InBoundaryConfig);

	ActualBoundaryMin = BoundaryConfig.BoxMin;
	ActualBoundaryMax = BoundaryConfig.BoxMax;

	Character = Cast<ACA_Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (bShowDebugBounds)
	{
		const float LocationZ = GetActorLocation().Z;
		
		Vertices = {
			FVector(ActualBoundaryMin.X, ActualBoundaryMin.Y, LocationZ),
			FVector(ActualBoundaryMax.X, ActualBoundaryMin.Y, LocationZ),
			FVector(ActualBoundaryMax.X, ActualBoundaryMax.Y, LocationZ),
			FVector(ActualBoundaryMin.X, ActualBoundaryMax.Y, LocationZ)
		};
	}
}

void ACA_BoundaryActor_Math_Push::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TrackCharacter();
	
	if (bShowDebugBounds)
	{
		DrawDebugBoundaries();
	}
}

void ACA_BoundaryActor_Math_Push::TrackCharacter() const
{
	if (!IsValid(Character))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character invalid"), __FUNCTION__);
		return;
	}

	const FVector CharacterLocation = Character->GetActorLocation();
	if (IsWithinBounds(CharacterLocation))
	{
		return;
	}

	const FVector Force = CalculateBoundaryForce(CharacterLocation);
	if (!Force.IsNearlyZero())
	{
		Character->PhysicalPushCharacter(Force, PushStrength, bPushWithImpulse);
	}
}

FVector ACA_BoundaryActor_Math_Push::CalculateBoundaryForce(const FVector& Position) const
{
	FVector Force = FVector::ZeroVector;

	if (Position.X < ActualBoundaryMin.X)
		Force.X = PushStrength;
	else if (Position.X > ActualBoundaryMax.X)
		Force.X = -PushStrength;

	if (Position.Y < ActualBoundaryMin.Y)
		Force.Y = PushStrength;
	else if (Position.Y > ActualBoundaryMax.Y)
		Force.Y = -PushStrength;

	return Force;
}

bool ACA_BoundaryActor_Math_Push::IsWithinBounds(const FVector& Position) const
{
	return Position.X >= ActualBoundaryMin.X &&
		   Position.X <= ActualBoundaryMax.X &&
		   Position.Y >= ActualBoundaryMin.Y &&
		   Position.Y <= ActualBoundaryMax.Y;
}

float ACA_BoundaryActor_Math_Push::GetDistanceToBoundary(const FVector& Position) const
{
	const float DistanceToLeft = Position.X - ActualBoundaryMin.X;
	const float DistanceToRight = ActualBoundaryMax.X - Position.X;
	const float DistanceToBottom = Position.Y - ActualBoundaryMin.Y;
	const float DistanceToTop = ActualBoundaryMax.Y - Position.Y;

	return FMath::Min(FMath::Min(DistanceToLeft, DistanceToRight), 
		FMath::Min(DistanceToBottom, DistanceToTop));
}

void ACA_BoundaryActor_Math_Push::DrawDebugBoundaries()
{
	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] World invalid"), __FUNCTION__);
		return;
	}

	for (int i = 0; i < Vertices.Num(); ++i)
	{
		DrawDebugLine(
			World,
			Vertices[i],
			Vertices[(i + 1) % Vertices.Num()],
			DebugBoundaryColor,
			false,
			-1.f,
			0,
			DebugLineThickness);
	}
}