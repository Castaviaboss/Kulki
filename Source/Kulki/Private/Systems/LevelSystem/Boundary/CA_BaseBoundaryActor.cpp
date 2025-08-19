// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/LevelSystem/Boundary/CA_BaseBoundaryActor.h"


ACA_BaseBoundaryActor::ACA_BaseBoundaryActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACA_BaseBoundaryActor::InitBoundary(const FLevelBoundaryConfiguration& InBoundaryConfig)
{
	BoundaryConfig = InBoundaryConfig;
}
