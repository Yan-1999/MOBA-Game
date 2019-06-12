// MOBA project group, SSE, Tonji University. Some rights reserved.



#pragma once



#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Monster.generated.h"



UENUM(BlueprintType)

enum class MonsterType :uint8

{

	Red UMETA(DisplayName = "Red buff"),

	Blue UMETA(DisplayName = "Blue buff"),

	Tyrant UMETA(DisplayName = "Tyrant")

};



UCLASS()

class MOBA_GAME_API AMonster : public APawn

{

	GENERATED_BODY()



public:

	// Sets default values for this pawn's properties

	AMonster();

	AMonster(MonsterType type);



protected:

	// Called when the game starts or when spawned

	virtual void BeginPlay() override;



	/**Monster current HP value. Minus value or above max is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|type", meta = (AllowPrivateAccess = "true"))

		MonsterType type_;



	/**Upper bound of Monster's current health. Zero value or below is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP", meta = (AllowPrivateAccess = "true"))

		float max_hp_;



	/**Monster current HP value. Minus value or above max is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|HP", meta = (AllowPrivateAccess = "true"))

		float cur_hp_;



	/**Monster current Speed. Minus value is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))

		float speed_;



	/**Monster attack frequncy. Minus value is INVAILD.*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|speed", meta = (AllowPrivateAccess = "true"))

		float atk_freq_;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))

		float drop_money_;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties|drop", meta = (AllowPrivateAccess = "true"))

		int drop_exp_;



public:



	/**Monser Attack*/

	float attack();



	// Called every frame

	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};