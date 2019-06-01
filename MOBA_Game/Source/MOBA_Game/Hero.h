// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MOBA_GameCharacter.h"
#include "Hero.generated.h"

//UENUM(BlueprintType)
//enum class Side :int8
//{
//	RED = -1 UMETA(DisplayName = "RED"),
//	NEUTRAL = 0 UMETA(DisplayName = "NEUTRAL"),
//	BLUE = 1 UMETA(DisplayName = "BLUE"),
//};

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
		float stablize_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
		float silence_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
		float dizziness_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
		float knock_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float damage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost", meta = (AllowPrivateAccess = "true"))
		float mp_needed_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown", meta = (AllowPrivateAccess = "true"))
		float cur_cd_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown", meta = (AllowPrivateAccess = "true"))
		float max_cd_;

};

/**<The Hero Class> AHero
 *Class for heroes in the MOBA game.
 *This class only contains properties and methods related to game process.
 *Other properties and methods should be in the AMOBA_GameCharacter class.
 */

UCLASS(BlueprintType)
class MOBA_GAME_API AHero : public AMOBA_GameCharacter
{
	GENERATED_BODY()

private:

	/**Hero's type.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Type", meta = (AllowPrivateAccess = "true"))
		HeroType type_;

	/**Hero's skill list.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Skill", meta = (AllowPrivateAccess = "true"))
		TArray<FHeroSkill> skill_;


public:
	//Constucters
	AHero();
	AHero(HeroType, decltype(skill_));


	//Basic return functions.
	FORCEINLINE float max_hp() { return max_hp_; }
	FORCEINLINE float hp() { return cur_hp_; }
	FORCEINLINE float re_hp() { return re_hp_; }
	FORCEINLINE float max_mp() { return max_mp_; }
	FORCEINLINE float mp() { return cur_mp_; }
	FORCEINLINE float re_mp() { return re_mp_; }
	FORCEINLINE float speed() { return speed_; }
	FORCEINLINE float atk_freq() { return atk_freq_; }
	FORCEINLINE int level() { return level_; }
	FORCEINLINE int exp() { return exp_; }
	FORCEINLINE int money() { return money_; }
	FORCEINLINE int drop_money() { return drop_money_; }
	FORCEINLINE int drop_exp() { return drop_exp_; }
	FORCEINLINE AActor* chosen_unit() { return chosen_unit_; }

	/**Called by MOBA_GamePlayerController, edit the unit chosen by the hero.*/
	AActor* ChoseUnit(AActor* pUnit);

	//Hero's actural damage. Return value is damage.
	auto AD(AActor* pUnit, float fDamage = 10.0f, float DegRange = 5.0f);

	UFUNCTION()
	void OnHit(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Hero's art attack. Return value is damage.
	auto AP(FHeroSkill& Skill);

	//Override the APawn::ShouldTakeDamage(). Return if hero should take the damage.
	bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	//Hero's HP&MP recovery.
	void Cure(float DeltaSeconds, float addtional_hp, float addtional_mp);

	//Hero's gain.
	void Grow(int, int);

	//Buy item.
	void Buy();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

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

	/**Hero's curren Speed. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/**Hero attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
		float atk_freq_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_;

	/** Exp of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_;

	/**Money owned by hero. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_money_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_exp_;

	UPROPERTY(BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		AActor* chosen_unit_;

	UPROPERTY(EditAnywhere, Category = Collision)
		class USphereComponent* range_;

};
