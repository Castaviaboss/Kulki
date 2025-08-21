// Fill out your copyright notice in the Description page of Project Settings.

#include "Kulki/Public/GameModeOverride/Character/CA_Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/Player/CA_PlayerData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kulki/Public/CA_GameInstance.h"
#include "Kulki/Public/Data/CA_GameData.h"
#include "Kulki/Public/Data/Input/CA_InputData.h"
#include "Kulki/Public/GameModeOverride/PlayerController/CA_PlayerController.h"
#include "Systems/AI/EnemyPawn/CA_EnemyCharacter.h"

DEFINE_LOG_CATEGORY(CharacterLog);

ACA_Character::ACA_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetSimulatePhysics(true);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetUsingAbsoluteScale(true);

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const UCA_GameInstance* GameInstance = CastChecked<UCA_GameInstance>(GetGameInstance());

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInput))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] EnhancedInput invalid"), __FUNCTION__);
		return;
	}

	const UCA_GameData* GameData = GameInstance->GameData;
	if (!IsValid(GameData))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] GameData invalid"), __FUNCTION__);
		return;
	}

	const UCA_InputData* InputData = GameData->InputData;
	if (!IsValid(InputData))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] InputData invalid"), __FUNCTION__);
		return;
	}

	EnhancedInput->BindAction(
		InputData->MousePressAction, ETriggerEvent::Started, this, &ACA_Character::StartMove);

	EnhancedInput->BindAction(
		InputData->MousePressAction, ETriggerEvent::Completed, this, &ACA_Character::StopMove);

	PlayerController = Cast<ACA_PlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] PlayerController invalid"), __FUNCTION__);
		return;
	}
	SetMappingContext(InputData->DefaultMappingContext);

	PlayerData = GameData->PlayerData;
	if (!IsValid(PlayerData))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] PlayerData invalid"), __FUNCTION__);
		return;
	}

	MaxForce = PlayerData->MaxForce;
	ForceMultiplier = PlayerData->ForceMultiplier;
	GetCharacterMovement()->MaxWalkSpeed = PlayerData->MaxSpeed;

	InitialOrthoWidth = CameraComponent->OrthoWidth;
	InitialTargetArmLenght = SpringArmComponent->TargetArmLength;
	InitialScaleAverage = (GetActorScale3D().X + GetActorScale3D().Y + GetActorScale3D().Z) / 3.0f;

	ApplyStartStats(
		PlayerData->StartStrength,
		PlayerData->StartSpeed,
		PlayerData->MassCoefficient,
		PlayerData->AbsorptionFactor);

	UpdateScaleFromStrength();
}

void ACA_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsMoving)
	{
		MoveTowardsMouse(DeltaSeconds);
	}
}

void ACA_Character::SetMappingContext(const UInputMappingContext* MappingContext, const int32 Priority) const
{
	if (!IsValid(PlayerController))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] PlayerController invalid"), __FUNCTION__);
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!IsValid(Subsystem))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] Subsystem invalid"), __FUNCTION__);
		return;
	}
	
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(MappingContext, Priority);
}

//Movement

FVector ACA_Character::UpdateMousePosition() const
{
	if (!IsValid(PlayerController))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] PlayerController invalid"), __FUNCTION__);
		return FVector::ZeroVector;
	}

	float MouseX, MouseY;
	if (PlayerController->GetMousePosition(MouseX, MouseY))
	{
		FVector WorldLocation, WorldDirection;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

		const float Distance = -WorldLocation.Z / WorldDirection.Z;
		return WorldLocation + WorldDirection * Distance;
	}
	
	return FVector::ZeroVector;
}

void ACA_Character::MoveTowardsMouse(const float DeltaTime) const
{
	if (!IsValid(GetCapsuleComponent()))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] CapsuleComponent invalid"), __FUNCTION__);
		return;
	}

	const FVector TargetPos = UpdateMousePosition();
	FVector Direction = TargetPos - GetActorLocation();
	Direction.Z = 0;
	
	const float Distance = Direction.Size();

	const float BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
	const float EffectiveSpeed = BaseSpeed * CurrentSpeed / (CurrentStrength * MassCoefficient);

	Direction.Normalize();
	const FVector CurrentVelocity = GetCapsuleComponent()->GetComponentVelocity();
	const FVector DesiredVelocity = Direction * EffectiveSpeed;
	
	FVector Force = (DesiredVelocity - CurrentVelocity) * ForceMultiplier;
	Force = Force.GetClampedToMaxSize(MaxForce);
	GetCapsuleComponent()->AddForce(Force / DeltaTime);
}

void ACA_Character::StartMove()
{
	bIsMoving = true;
}

void ACA_Character::StopMove()
{
	bIsMoving = false;
}

//Movement

void ACA_Character::PhysicalPushCharacter(
	const FVector& Force,
	const float PushStrength,
	const bool bImpulse)
{
	if (!IsValid(GetCapsuleComponent()))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] CapsuleComponent invalid"), __FUNCTION__);
		return;
	}

	FVector PushDirection = Force;
	PushDirection.Z = 0.f;

	if (!PushDirection.IsNearlyZero())
	{
		PushDirection.Normalize();
		const FVector PushForce = PushDirection * PushStrength;

		if (bImpulse)
		{
			GetCapsuleComponent()->AddImpulse(PushForce, NAME_None, true);
		}
		else
		{
			GetCapsuleComponent()->AddForce(PushForce);
		}
	}
}

void ACA_Character::NotifyHit(
	class UPrimitiveComponent* MyComp,
	AActor* Other,
	class UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
	if (ACA_EnemyCharacter* Enemy = Cast<ACA_EnemyCharacter>(Other))
	{
		const EEnemyLeaderStats TypeStat = Enemy->LeaderStat;
		if (Enemy->TryAbsorb(this))
		{
			if (OnEnemyAbsorbed.IsBound())
			{
				OnEnemyAbsorbed.Broadcast(TypeStat);
			}
		}
	}
}

//Stats Calculating

void ACA_Character::AddStrength(const float StrengthToAdd)
{
	Super::AddStrength(StrengthToAdd);
	UpdateScaleFromStrength();
}

void ACA_Character::ReduceStrength(const float StrengthToReduce)
{
	Super::ReduceStrength(StrengthToReduce);
	UpdateScaleFromStrength();
}

//Stats Calculating

void ACA_Character::UpdateScaleFromStrength()
{
	if (CurrentStrength >= PlayerData->AvailableStrengthRange.Y
		|| CurrentStrength <= PlayerData->AvailableStrengthRange.X)
	{
		return;
	}
	
	if (!IsValid(CameraComponent))
	{
		UE_LOG(CharacterLog, Error, TEXT("[%hs] CameraComponent invalid"), __FUNCTION__);
		return;
	}
	
	const float NewScale = CurrentStrength;
	
	SetActorScale3D(FVector(NewScale));

	float ScaleRatio = NewScale / InitialScaleAverage;
	
	if (ScaleRatio < 1.0f)
	{
		ScaleRatio = FMath::Lerp(1.0f, ScaleRatio, 0.3f);
	}
	
	const float NewOrthoWidth = (InitialOrthoWidth * ScaleRatio) * PlayerData->CameraHeightFactor;
	const float NewTargetArmLenght = (InitialTargetArmLenght * ScaleRatio) * PlayerData->CameraHeightFactor;

	CameraComponent->OrthoWidth = NewOrthoWidth;
	SpringArmComponent->TargetArmLength = NewTargetArmLenght;
}

//Stats Calculating
