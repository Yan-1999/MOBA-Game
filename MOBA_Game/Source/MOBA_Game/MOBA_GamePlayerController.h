// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MOBA_GamePlayerController.generated.h"

UCLASS()
class AMOBA_GamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMOBA_GamePlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	virtual void SetPawn(APawn* InPawn)override;

	void OnMyHeroDeath();

	void MyHeroRespawn();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn", meta = (AllowPrivateAccess = "true"))
		float respawn_time_ = 5.0f;

	FTimerHandle respawn_timer_;

	class AHero* MyHero = nullptr;

};
