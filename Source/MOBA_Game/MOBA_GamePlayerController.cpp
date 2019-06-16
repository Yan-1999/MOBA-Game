// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#include "MOBA_GamePlayerController.h"

#include "MOBA_GameGameMode.h"
#include "MOBA_GameGameState.h"
#include "Minion.h"
#include "Monster.h"
#include "Turret.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MOBA_GameCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "TimerManager.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

AMOBA_GamePlayerController::AMOBA_GamePlayerController()
	:side_(ESide::RED), type_(EHeroType::ADC)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	abilities_.SetNum(3);
}

void AMOBA_GamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPawn())
	{
		GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Black, "have");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Black, "no");
	}
}

void AMOBA_GamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMOBA_GamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMOBA_GamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMOBA_GamePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMOBA_GamePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMOBA_GamePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMOBA_GamePlayerController::OnResetVR);
}

void AMOBA_GamePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMOBA_GamePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AMOBA_GameCharacter * MyPawn = Cast<AMOBA_GameCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Pawn, false, Hit);
		AActor* SelectedActor = Hit.GetActor();

		//If a unit is selected, move to it.
		if ((Cast<AHero>(SelectedActor) || Cast<AMinion>(SelectedActor) || Cast<AMonster>(SelectedActor) || Cast<ATurret>(SelectedActor)))
		{
			if (AHero * MyHero = Cast<AHero>(GetPawn()))
			{
				MyHero->ChooseUnit(SelectedActor);
				UAIBlueprintHelperLibrary::SimpleMoveToActor(this, SelectedActor);
			}
		}
		else if (Hit.bBlockingHit)
		{
			if (AHero * MyHero = Cast<AHero>(GetPawn()))
			{
				MyHero->ChooseUnit(nullptr);
			}
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AMOBA_GamePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMOBA_GamePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMOBA_GamePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMOBA_GamePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMOBA_GamePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		if (AHero * MyHero = Cast<AHero>(InPawn))
		{
			//MyHero->OnDeath.AddUniqueDynamic(this, &AMOBA_GamePlayerController::OnMyHeroDeath);
		}
	}
}

void AMOBA_GamePlayerController::OnMyHeroDeath()
{
	GEngine->AddOnScreenDebugMessage(8, 1.0f, FColor::Red, TEXT("Dead"));
	//MyHero = Cast<AHero>(GetPawn());
	PlayerState->bIsSpectator = true;
	ChangeState(NAME_Spectating);
	GetWorldTimerManager().SetTimer(respawn_timer_, this, &AMOBA_GamePlayerController::MyHeroRespawn, respawn_time_, false);
}

void AMOBA_GamePlayerController::MyHeroRespawn()
{
	TArray<AActor*> PlayerStarts;
	GetWorldTimerManager().ClearTimer(respawn_timer_);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	if (PlayerStarts.Num())
	{
		AActor* SpawnTarget = PlayerStarts[0];
		FRotator StartRotation(ForceInit);
		StartRotation.Yaw = SpawnTarget->GetActorRotation().Yaw;
		FVector StartLocation = SpawnTarget->GetActorLocation();
		FTransform Transform = FTransform(StartRotation, StartLocation);
		UClass* MyHeroClass = UGameplayStatics::GetGameMode(this)->DefaultPawnClass;
		if (MyHeroClass)
		{
			AHero* MyNewHero = GetWorld()->SpawnActorDeferred<AHero>(MyHeroClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

			if (MyNewHero)
			{
				Possess(MyNewHero);
				MyNewHero->Set(this);
				PlayerState->bIsSpectator = false;
				ChangeState(NAME_Playing);
				UGameplayStatics::FinishSpawningActor(MyNewHero, Transform);
			}
		}
	}
}
