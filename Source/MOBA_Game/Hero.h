// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MOBA_GameCharacter.h"
#include "Hero.generated.h"

/**<The Hero Class> AHero
 *Class for heroes in the MOBA game.
 *This class only contains properties and methods related to game process. Other properties and methods should be in the AMOBA_GameCharacter class.
 */
UCLASS()
class MOBA_GAME_API AHero : public AMOBA_GameCharacter
{
	GENERATED_BODY()

private:
	/**Upper bound of hero's current health. Zero value or below is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_hp_;

	/**Hero's current HP value. Zero value means death. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_hp_;

	/** Inherent speed of HP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_hp_;

	/**Hero's max MP value. Used as an upper bound of current magic power.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_mp_;

	/**Hero's current MP value. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_mp_;

	/** Inherent speed of MP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_mp_;

	/**Minion curren Speed. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/**Hero attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float atk_freq_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_;

	/** EXP of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_;

	/**Money owned by hero. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		float drop_money_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_exp_;

public:
	AHero();

	/**Basic functions.*/
	FORCEINLINE float max_hp() { return max_hp_; }
	FORCEINLINE float hp() { return cur_hp_; }
	FORCEINLINE float re_hp() { return re_hp_; }
	FORCEINLINE float max_mp() { return max_mp_; }
	FORCEINLINE float mp() { return cur_mp_; }
	FORCEINLINE float re_mp() { return re_mp_; }
	FORCEINLINE float speed() { return speed_; }
	FORCEINLINE int level() { return level_; }
	FORCEINLINE float exp() { return exp_; }
	FORCEINLINE float money() { return money_; }

	/**Hero's art attack. Return value is damage.*/
	float Art();

	/**Hero's HP&MP recovery.*/
	void Cure(float addtional_hp, float addtional_mp);

	/**Hero's Money gain.*/
	void Grow(int gain);

	/**Buy item*/
	void Buy();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
};