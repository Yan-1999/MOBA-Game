// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include<utility>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

/**<The Turret Class> ATurret
 *Class for turrets in the MOBA game.
 */

UCLASS()
class MOBA_GAME_API ATurret : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret();

	//Turret's AD
	auto AD();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/**Pair of turret's health.
	*First: turret's current health.
	*Second: turret's max health.
	*Zero value or below is INVAILD.*/
	::std::pair<float, float> hp_;

};
