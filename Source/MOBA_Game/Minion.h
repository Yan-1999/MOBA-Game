
// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include <utility>
#include"Engine\World.h"
#include"Hero.h"
#include "CoreMinimal.h"
#include"Perception\AIPerceptionStimuliSourceComponent.h"
#include "Minion.generated.h"
/**<The Minion's Type Struct> MinionType

*Struct for minion's type data.

*/
UENUM(BlueprintType)

//a enum class to define miniontype
enum class MinionType :uint8

{

	Melee UMETA(DisplayName = "Melee creeps"),

	Remote UMETA(DisplayName = "Remote soldier"),

	Artillery UMETA(DisplayName = "Artillery Corps")

};

//a enum class to define road
enum class road :uint8

{

	up UMETA(DisplayName = "up"),

	mid UMETA(DisplayName = "mid"),

	down UMETA(DisplayName = "down")

};


UCLASS()

class MOBA_GAME_API AMinion : public ACharacter

{

	GENERATED_BODY()

public:

	//Constructers
	AMinion();

	AMinion(MinionType type);

	AMinion(road Road)
	{
		Road = ROAD;
	}


	//Road and type
	road ROAD;

	MinionType type_;


	class UNavigationSystemV1* findwayto;

	FORCEINLINE float speed() { return speed_; }

	FORCEINLINE float atk_freq() { return attack_freq_; }



	void Attack(AActor* Target, MinionType type);

	void drop(AHero* Damagecauser);

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	/*bool minDistance(AActor * Target) const;*/






	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)

		void BeginOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)

		void EndOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
		AActor* ChoseUnit(AActor* Target);


	UFUNCTION()
		void ChosenUnitAD();

protected:

	// Called when the game starts or when spawned


	virtual void BeginPlay() override;



private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))

		float attack_freq_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))

		AActor* chosen_unit_ = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))

		FTimerHandle attack_timer_;


	UPROPERTY(EditAnywhere, Category = Collision)

		class USphereComponent* ad_range_;

	UPROPERTY(EditAnywhere, Category = See)

		class UAIPerceptionComponent* Sight;


	UPROPERTY(EditAnywhere, Category = See)
		class UAIPerceptionStimuliSourceComponent* Stimulus;


	/**Minion current Speed. Minus value is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))

		float speed_;

	/**Minion attack frequncy. Minus value is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))

		float atk_freq_ = 2.0f;

	/*Minion's hp*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float max_hp = 1000.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float cur_hp = max_hp;

	/*Minion drop*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		int drop_money_ = 200;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		int drop_exp_ = 200;

};