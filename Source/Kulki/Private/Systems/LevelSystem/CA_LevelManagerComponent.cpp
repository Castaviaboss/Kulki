// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/Systems/LevelSystem/CA_LevelManagerComponent.h"

#include "PaperSprite.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Kulki/Public/CA_GameInstance.h"
#include "Kulki/Public/Data/CA_GameData.h"
#include "Kulki/Public/Data/Level/CA_LevelData.h"
#include "Kulki/Public/Systems/LevelSystem/Boundary/CA_BaseBoundaryActor.h"

DEFINE_LOG_CATEGORY(LevelManagerLog);

UCA_LevelManagerComponent::UCA_LevelManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCA_LevelManagerComponent::InitManager()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] World invalid"), __FUNCTION__);
		return;
	}

	const UCA_GameInstance* GameInstance = CastChecked<UCA_GameInstance>(World->GetGameInstance());

	const UCA_GameData* GameData = GameInstance->GameData;
	if (!IsValid(GameData))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] GameData invalid"), __FUNCTION__);
		return;
	}

	const UCA_LevelData* LevelData = GameData->LevelData;
	if (!IsValid(LevelData))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] LevelData invalid"), __FUNCTION__);
		return;
	}

	SetupPlane(LevelData, World);
	SetupBoundary(LevelData, World);
}

void UCA_LevelManagerComponent::SetupPlane(const UCA_LevelData* LevelData, UWorld* World)
{
	if (LevelData->PlaneConfiguration.PlaneActorClass.IsNull())
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] PlaneActor is null"), __FUNCTION__);
		return;
	}

	UClass* PlaneActorClass = LevelData->PlaneConfiguration.PlaneActorClass.LoadSynchronous();
	if (!IsValid(PlaneActorClass))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] LevelActorClass invalid"), __FUNCTION__);
		return;
	}
	
	PlaneActor = World->SpawnActor<APaperSpriteActor>(
		PlaneActorClass, 
		LevelData->PlaneConfiguration.PlaneTransform,
		FActorSpawnParameters()
	);
	if (!IsValid(PlaneActor))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] PlaneActor invalid"), __FUNCTION__);
		return;
	}
	
	const FLevelPlaneConfiguration& Config = LevelData->PlaneConfiguration;
	if (Config.SourceSprite.IsNull())
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] SourceSprite null"), __FUNCTION__);
		return;
	}

	if (Config.Material.IsNull())
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] SpriteComponent null"), __FUNCTION__);
		return;
	}

	UPaperSpriteComponent* SpriteComponent = PlaneActor->GetRenderComponent();
	if (!IsValid(SpriteComponent))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] SpriteComponent invalid"), __FUNCTION__);
		return;
	}

	UPaperSprite* Sprite = Config.SourceSprite.LoadSynchronous();
	if (!IsValid(Sprite))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] Sprite invalid"), __FUNCTION__);
		return;
	}

	UMaterialInstance* Material = Config.Material.LoadSynchronous();
	if (!IsValid(Material))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] Material invalid"), __FUNCTION__);
		return;
	}
	
	UMaterialInstanceDynamic* MaterialDynamic = UMaterialInstanceDynamic::Create(Material, this);
	if (!IsValid(MaterialDynamic))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] Failed to create MaterialDynamic"), __FUNCTION__);
		return;
	}

	if (!Config.MaterialParameters.IsEmpty())
	{
		for (const FMaterialParameter& Param : Config.MaterialParameters)
		{
			MaterialDynamic->SetScalarParameterValue(Param.ParameterName, Param.Value);
		}
	}

	SpriteComponent->SetSprite(Sprite);
	SpriteComponent->SetSpriteColor(Config.SpriteColor);
	
	SpriteComponent->SetMaterial(DefaultMaterialIndex, MaterialDynamic);
}

void UCA_LevelManagerComponent::SetupBoundary(const UCA_LevelData* LevelData, UWorld* World)
{
	if (LevelData->BoundaryConfiguration.BoundaryActorClass.IsNull())
	{
		return;
	}

	UClass* BoundaryActorClass = LevelData->BoundaryConfiguration.BoundaryActorClass.LoadSynchronous();
	if (!IsValid(BoundaryActorClass))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] BoundaryActorClass invalid"), __FUNCTION__);
		return;
	}
	
	BoundaryActor = World->SpawnActor<ACA_BaseBoundaryActor>(
		BoundaryActorClass,
		FActorSpawnParameters()
	);
	if (!IsValid(BoundaryActor))
	{
		UE_LOG(LevelManagerLog, Error, TEXT("[%hs] BoundaryActor invalid"), __FUNCTION__);
		return;
	}

	BoundaryActor->InitBoundary(LevelData->BoundaryConfiguration);
}
