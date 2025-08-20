// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CA_LevelData.generated.h"

class APaperSpriteActor;
class UPaperSprite;
class ACA_BaseBoundaryActor;

USTRUCT(BlueprintType)
struct FMaterialParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value = 1.0f;
};

USTRUCT(BlueprintType)
struct FLevelPlaneConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TSoftClassPtr<APaperSpriteActor> PlaneActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	FTransform PlaneTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
	TSoftObjectPtr<UMaterialInstance> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
	TArray<FMaterialParameter> MaterialParameters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	TSoftObjectPtr<UPaperSprite> SourceSprite;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	FLinearColor SpriteColor = FLinearColor::White;
};

UENUM(BlueprintType)
enum class EBoundaryShapeType : uint8
{
	Box		UMETA(DisplayName="Box"),
	Sphere	UMETA(DisplayName="Sphere"),
	Custom	UMETA(DisplayName="Custom")
};

USTRUCT(BlueprintType)
struct FLevelBoundaryConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TSoftClassPtr<ACA_BaseBoundaryActor> BoundaryActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boundaries")
	EBoundaryShapeType ShapeType = EBoundaryShapeType::Box;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box Boundaries", meta=(EditCondition="ShapeType==EBoundaryShapeType::Box"))
	FVector BoxMin = FVector(-1000.0f, -1000.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box Boundaries", meta=(EditCondition="ShapeType==EBoundaryShapeType::Box"))
	FVector BoxMax = FVector(1000.0f, 1000.0f, 50.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sphere Boundaries", meta=(EditCondition="ShapeType==EBoundaryShapeType::Sphere"))
	float SphereRadius = 100.f;
};

UCLASS()
class KULKI_API UCA_LevelData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	FLevelPlaneConfiguration PlaneConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	FLevelBoundaryConfiguration BoundaryConfiguration;
};
