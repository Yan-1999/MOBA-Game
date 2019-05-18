// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MOBA_GameCharacter.h"
#include "Hero.generated.h"

/**
 *
 */
UCLASS()
class MOBA_GAME_API AHero : public AMOBA_GameCharacter
{
	GENERATED_BODY()

private:
	/**Upper bound of hero's current health. Zero value or below is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_health_;

	/**Hero's current HP value. Zero value means death. Minus value or above max is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_health_;

	/** Speed of HP Recovery PER SECOND. Can be minus.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_health_;

	/**Hero's max MP value. Used as an upper bound of current magic power.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_magic_;

	/**Hero's current MP value. Minus value or above max is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_magic_;

	/** Speed of MP Recovery PER SECOND. Can be minus.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_magic_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_;

	/** EXP of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_;

	/**Money owned by hero. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_;

public:
	AHero();

	/**Art attack. Return value is damage.*/
	float Art();

	/**HP&MP recovery.*/
	void Cure();

	/**HP recovery.*/
	void Heal();

	/**Money gain.*/
	void Grow();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
};
