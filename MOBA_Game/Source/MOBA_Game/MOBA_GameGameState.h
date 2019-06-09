// MOBA project group, SSE, Tonji University. Some rights reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MOBA_GameGameState.generated.h"

UENUM(BlueprintType)
enum class ESide :uint8
{
	RED = 0 UMETA(DisplayName = "RED"),
	BLUE = 1 UMETA(DisplayName = "BLUE"),
	NEUTRAL = 2 UMETA(DisplayName = "NEUTRAL"),
	OTHER = 3 UMETA(DisplayName = "OTHER")
};

USTRUCT(BlueprintType)
struct FGroup
{
	GENERATED_USTRUCT_BODY()

public:
	ESide side_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (AllowPrivateAccess = "true"))
		int score_ = 0;

	TArray<class AHero*>heroes_;
	TArray<class AMinion*>minions_;
	TArray<class ATurret*>turrets_;
};

/**
 *
 */
UCLASS()
class MOBA_GAME_API AMOBA_GameGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMOBA_GameGameState();

	bool Join(AActor* const pUnit, ESide side);

	void Leave(AActor* const pUnit);

	ESide IsInSide(const AActor* const pUnit);

	bool IsSameSide(const AActor* const pLhs, const AActor* const pRhs);

	void Kill(AActor* pKiller, AActor* pKilled);

private:
	TArray<FGroup> groups_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FTimerHandle global_timer_;

};
