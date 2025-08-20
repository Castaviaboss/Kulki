// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/AI/EnemyPawn/CA_EnemyCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Data/AI/CA_EnemyCharacterData.h"

ACA_EnemyCharacter::ACA_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereDetector = CreateDefaultSubobject<USphereComponent>("SphereDetector");
	SphereDetector->SetupAttachment(RootComponent);
}

void ACA_EnemyCharacter::InitCharacter(
	UCA_EnemyCharacterData* Config,
	AActor* CenterOfSpawn)
{
	if (!IsValid(Config))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Config invalid"), __FUNCTION__);
		return;
	}
	
	if (Config->SourceFlipbook.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] SourceFlipbook null"), __FUNCTION__);
		return;
	}

	UPaperFlipbookComponent* FlipbookComponent = GetSprite();
	if (!IsValid(FlipbookComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] FlipbookComponent invalid"), __FUNCTION__);
		return;
	}

	UPaperFlipbook* Flipbook = Config->SourceFlipbook.LoadSynchronous();
	if (!IsValid(Flipbook))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Flipbook invalid"), __FUNCTION__);
		return;
	}
	
	FlipbookComponent->SetFlipbook(Flipbook);
	FlipbookComponent->SetSpriteColor(Config->SpriteColor);

	if (!IsValid(SphereDetector))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] SphereDetector invalid"), __FUNCTION__);
		return;
	}
	SphereDetector->SetSphereRadius(Config->SphereDetectorRadius);
}
