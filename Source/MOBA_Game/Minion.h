// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include <utility>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minion.generated.h"

/**<The Minion's Type Struct> MinionType
*Struct for minion's type data.
*/

UENUM(BlueprintType)
enum class MinionType :uint8
{
	Melee UMETA(DisplayName = "Melee creeps"),
	Remote UMETA(DisplayName = "Remote soldier"),
	Artillery UMETA(DisplayName = "Artillery Corps")
};

/**<The Minion Class> AMinion
 *Class for minions in the MOBA game.
 */

UCLASS()
class MOBA_GAME_API AMinion : public APawn
{
	GENERATED_BODY()

public:
	//Constructers
	AMinion();
	AMinion(MinionType type);

	//Basic return functions
	FORCEINLINE auto hp() { return hp_; }
	FORCEINLINE float speed() { return speed_; }
	FORCEINLINE float atk_freq() { return atk_freq_; }
	FORCEINLINE auto drop() { return drop_; }

	//Minion attack
	auto AD();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/**Minion current HP value. Minus value or above max is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|type", meta = (AllowPrivateAccess = "true"))
		MinionType type_;

	/**Pair of minion's health.
	*First: minion's current health.
	*Second: minion's max health.
	*Zero value or below is INVAILD.*/
	::std::pair <float, float> hp_;

	/**Minion current Speed. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/**Minion attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float atk_freq_;

	/**Money&exp droped when killed.
	*First: Money droped.
	Second: Exp droped.
	*Minus value is INVAILD.*/
	::std::pair<int, int> drop_;

};

UCLASS()
class AWeaponActor :public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE class UBoxComponent* GetWeaponCollision() { return WeaponCollision; }
	void ActiveAttack();
	void DeactiveAttack();
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool bCanAttack;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|type", meta = (AllowPrivateAccess = "true"))
		float damage;
	UPROPERTY(EditAnywhere, Category = Collision)
		class UBoxComponent* WeaponCollision;

};
