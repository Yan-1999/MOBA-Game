// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include <utility>

#include "CoreMinimal.h"
#include "MOBA_GameCharacter.h"
#include "Hero.generated.h"

/**<The Hero's Type Struct> HeroType
*Struct for hero's type data.
*/

UENUM(BlueprintType)
enum class HeroType :uint8
{
	ADC UMETA(DisplayName = "Attack Damage Carry"),
	APC UMETA(DisplayName = "Ability Power Carry"),
	Tank UMETA(DisplayName = "Tank"),
	Support UMETA(DisplayName = "Support"),
	Assassin UMETA(DisplayName = "Assassin")
};

/**<The Skill Struct> Skill
*Struct for hero's skill data.
*/

USTRUCT(BlueprintType)
struct FHeroSkill
{
	GENERATED_USTRUCT_BODY()

public:
};

/**<The Hero Class> AHero
 *Class for heroes in the MOBA game.
 *This class only contains properties and methods related to game process.
 *Other properties and methods should be in the AMOBA_GameCharacter class.
 */

UCLASS()
class MOBA_GAME_API AHero : public AMOBA_GameCharacter
{
	GENERATED_BODY()

private:
	/**Pair of hero's health.
	*First: hero's current health.
	*Second: hero's max health.
	*Zero value or below is INVAILD.*/
	::std::pair<float, float> hp_;

	/**Pair of hero's magic.
	*First: hero's current health.
	*Second: hero's max health.
	*Zero value or below is INVAILD.*/
	::std::pair<float, float> mp_;

	/**Pair of hero's recovery.
	*First: hero's health recovery speed.
	*Second: hero's magic recovery speed.
	*Zero value or below is INVAILD.*/
	::std::pair<float, float> recover_;

	/**Money&exp droped by hero when killed.
	*First: Money droped.
	*Second: Exp droped.
	*Minus value is INVAILD.*/
	::std::pair<int, int> drop_;

public:
	//Constucters
	AHero();
	AHero(HeroType, FHeroSkill);

	//Basic return functions.
	FORCEINLINE auto hp() { return hp_; }
	FORCEINLINE auto mp() { return mp_; }
	FORCEINLINE auto recover() { return recover_; }
	FORCEINLINE float speed() { return speed_; }
	FORCEINLINE float atk_freq() { return atk_freq_; }
	FORCEINLINE int level() { return level_; }
	FORCEINLINE float exp() { return exp_; }
	FORCEINLINE float money() { return money_; }
	FORCEINLINE auto drop() { return drop_; }

	//Hero's actural damage. Return value is damage.
	auto AD();

	//Hero's art attack. Return value is damage.
	auto AP(FHeroSkill skill);

	//Hero's HP&MP recovery.
	void Cure(float addtional_hp, float addtional_mp);

	//Hero's gain.
	void Grow(decltype(drop_) gain);

	//Buy item.
	void Buy();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:
	/**Hero's type.*/
	HeroType type_;

	/**Hero's skill list.*/
	FHeroSkill skill_;


	/**Minion curren Speed. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/**Hero attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
		float atk_freq_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_;

	/** Exp of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_;

	/**Money owned by hero. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_;


};
