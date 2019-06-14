// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Hero.h"
#include "MOBA_GamePlayerController.generated.h"

enum class ESide :uint8;

UCLASS()
class AMOBA_GamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMOBA_GamePlayerController();

	virtual void BeginPlay()override;

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

public:
	void OnMyHeroDeath();

	void MyHeroRespawn();

private:
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Side", meta = (AllowPrivateAccess = "true"))
		ESide side_;

	/**Hero's type.*/
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Type", meta = (AllowPrivateAccess = "true"))
		EHeroType type_;

	/**Hero's skill list.*/
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Ability", meta = (AllowPrivateAccess = "true"))
		TArray<FHeroAbility> abilities_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_ = 0;

	/** Exp of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_ = 0;

	/**Money owned by hero. Minus value is INVAILD.*/
	friend AHero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_ = 0;

	//friend AHero;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
	//	float max_hp_;

	//friend AHero;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
	//	float max_mp_;

	//friend AHero;
	///**Inherent speed of MP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
	//	float re_hp_;

	//friend AHero;
	///**Inherent speed of MP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
	//	float re_mp_;

	//friend AHero;
	///**Hero's resistance to AD. (1 - ad_resist_) is percentage of actual damage of AD. Minus value is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
	//	float ad_resist_;

	//friend AHero;
	///**Hero's resistance to AP. (1 - ad_resist_) is percentage of actual damage of AP. Minus value is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
	//	float ap_resist_;

	//friend AHero;
	///**Hero's curren Speed. Minus value is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
	//	float speed_;


	//friend AHero;
	///**Hero attack frequncy. Minus value is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))
	//	float ad_freq_;

	//friend AHero;
	///**Hero attack frequncy. Minus value is INVAILD.*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))
	//	float ad_damage_;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn", meta = (AllowPrivateAccess = "true"))
		float respawn_time_ = 1.0f;

	FTimerHandle respawn_timer_;

	class AHero* MyHero = nullptr;

};
