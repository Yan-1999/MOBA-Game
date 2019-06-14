// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MOBA_GameCharacter.h"
#include "Hero.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeroDelegate);

class UDamageType;
enum class ESide :uint8;

/**<The Hero's Type Struct> HeroType
*Struct for hero's type data.
*/
UENUM(BlueprintType)
enum class EHeroType :uint8
{
	ADC = 0 UMETA(DisplayName = "Attack Damage Carry"),
	APC UMETA(DisplayName = "Ability Power Carry"),
	Tank UMETA(DisplayName = "Tank"),
	Support UMETA(DisplayName = "Support"),
	Assassin UMETA(DisplayName = "Assassin")
};

/**<The Skill Struct> Skill
*Struct for hero's skill data.
*/
USTRUCT(BlueprintType)
struct FHeroAbility
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type", meta = (AllowPrivateAccess = "true"))
		bool aoe_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type", meta = (AllowPrivateAccess = "true"))
		float range_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = "true"))
		float stablize_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float damage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cost", meta = (AllowPrivateAccess = "true"))
		float mp_needed_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown", meta = (AllowPrivateAccess = "true"))
		float cur_cd_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown", meta = (AllowPrivateAccess = "true"))
		float max_cd_;

};

UCLASS()
class UAbilityDamageType :public UDamageType
{
	GENERATED_BODY()

public:
	UAbilityDamageType();
};

UCLASS()
class UHealType :public UDamageType
{
	GENERATED_BODY()

public:
	UHealType();
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
	ESide side_;

	/**Hero's type.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Type", meta = (AllowPrivateAccess = "true"))
		EHeroType type_;

	/**Hero's skill list.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Ability", meta = (AllowPrivateAccess = "true"))
		TArray <FHeroAbility> abilities_;

public:
	//Constucters
	AHero();

	void BeginPlay()override;

	//Basic return functions.
	FORCEINLINE float max_hp() { return max_hp_; }
	FORCEINLINE float hp() { return cur_hp_; }
	FORCEINLINE float re_hp() { return re_hp_; }
	FORCEINLINE float max_mp() { return max_mp_; }
	FORCEINLINE float mp() { return cur_mp_; }
	FORCEINLINE float re_mp() { return re_mp_; }
	FORCEINLINE float ad_resist() { return ad_resist_; }
	FORCEINLINE float ap_resist() { return ap_resist_; }
	FORCEINLINE float speed() { return speed_; }
	FORCEINLINE float atk_freq() { return ad_freq_; }
	FORCEINLINE int level() { return level_; }
	FORCEINLINE int exp() { return exp_; }
	FORCEINLINE int money() { return money_; }
	FORCEINLINE TArray<int> armour() { return items_; }
	FORCEINLINE int drop_money() { return drop_money_; }
	FORCEINLINE int drop_exp() { return drop_exp_; }
	FORCEINLINE AActor* chosen_unit() { return chosen_unit_; }

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Called by MOBA_GamePlayerController, edit the unit chosen by the hero.
	AActor* ChooseUnit(AActor* pChosenUnit);

	//Hero's actural damage. Return value is damage.
	UFUNCTION(BlueprintCallable, Category = "Damage")
		float AD(AActor* pUnit, float fAddDamageAmount);

	UFUNCTION()
		void BeginOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ChosenUnitAD();

	//Hero's art attack. Return value is damage.
	UFUNCTION(BlueprintCallable, Category = "Damage")
		float AP(FHeroAbility& Ability);

	void Ability_Q();
	void Ability_W();
	void Ability_E();
	//void Ability_R();

	//Override the APawn::ShouldTakeDamage(). Return if hero should take the damage.
	bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void Death();

	//Hero's HP&MP recovery.
	void Cure(float DeltaSeconds, float addtional_hp, float addtional_mp);

	//Hero's gain.
	void Grow(int, int);

	//Hero's inherent gain.
	void InherentGrow();

	//Buy item.
	UFUNCTION(BlueprintCallable, Category = "Shop")
		void Buy(int ItemID);

	//Buy item.
	UFUNCTION(BlueprintCallable, Category = "Shop")
		void Sell(int ItemID);

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	void Set(class AMOBA_GamePlayerController* MyPlayerController);

	//void Set(ESide side, EHeroType Type, decltype(abilities_)& arrAbilities, float fMaxHp, float fMaxMp, float fReHp, float fReMp, float fAdResist, float fApResist, float fAdFreq, float fAdDamage, int Level, int Exp, int Money);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death", meta = (AllowPrivateAccess = "true"))
	//	FHeroDelegate OnDeath;

private:
	/**Upper bound of hero's current health. Zero value or below is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_hp_;

	/**Hero's current HP value. Zero value means death. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_hp_;

	/**Inherent speed of HP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_hp_;

	/**Hero's max MP value. Used as an upper bound of current magic power.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float max_mp_;

	/**Hero's current MP value. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float cur_mp_;

	/**Inherent speed of MP Recovery PER SECOND. Minus value or above max is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|HP&MP", meta = (AllowPrivateAccess = "true"))
		float re_mp_;

	/**Hero's resistance to AD. (1 - ad_resist_) is percentage of actual damage of AD. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
		float ad_resist_;

	/**Hero's resistance to AP. (1 - ad_resist_) is percentage of actual damage of AP. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
		float ap_resist_;

	/**Hero's addtional to AD. (1 - ad_resist_) is percentage of actual damage of AD. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
		float ad_resist_add_ = 0;

	/**Hero's addtional to AP. (1 - ad_resist_) is percentage of actual damage of AP. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Resistance", meta = (AllowPrivateAccess = "true"))
		float ap_resist_add_ = 0;

	/**Hero's curren Speed. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/** Level of Hero. Used to determine hero's max HP & MP.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int level_ = 0;

	/** Exp of Hero. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int exp_ = 0;

	/** Max Exp of the level. Used to determine hero's level. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Level", meta = (AllowPrivateAccess = "true"))
		int max_exp_ = 0;

	/**Money owned by hero. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Money", meta = (AllowPrivateAccess = "true"))
		int money_ = 0;

	/**Hero's armour array. Use int as ID.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|Item", meta = (AllowPrivateAccess = "true"))
		TArray<int> items_;

	/**Money dropped when died.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_money_ = 100.0f;

	/**Exp dropped when died.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_exp_ = 100;

	/**Hero attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))
		float ad_freq_;

	/**Hero attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))
		float ad_damage_;

	/**AD timer.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		FTimerHandle ad_timer_;

	/**Unit chosed by hero. Used when hero decided to apply AD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		AActor* chosen_unit_ = nullptr;

	/**Sphere collider triggering AD. Symbolizing AD range.*/
	UPROPERTY(EditAnywhere, Category = Collision)
		class USphereComponent* ad_range_ = nullptr;

	FTimerHandle gain_timier_;

};
