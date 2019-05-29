// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Minion.generated.h"

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
	UCLASS();
class MOBA_GAME_API AMinion : public APawn
{
	GENERATED_BODY();

public:
	// Sets default values for this pawn's properties
	AMinion();
	AMinion(MinionType type);
	bool bCanAttack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**Minion current HP value. Minus value or above max is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|type", meta = (AllowPrivateAccess = "true"))
		MinionType type_;

	/**Upper bound of minion's current health. Zero value or below is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP", meta = (AllowPrivateAccess = "true"))
		float max_hp_=1000;

	/**Minion current HP value. Minus value or above max is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP", meta = (AllowPrivateAccess = "true"))
		float cur_hp_;

	/**Minion current Speed. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float speed_;

	/**Minion attack frequncy. Minus value is INVAILD.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))
		float atk_freq_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		float drop_money_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))
		int drop_exp_;

public:

	/**Minion Attack*/

	float Attack()

	{
	}
	//这里应该有一个判断是否播放了攻击动画的函数？但我还不会写。。


	// Called every frame
	virtual void Tick(float DeltaTime) override
	{
	}
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};














