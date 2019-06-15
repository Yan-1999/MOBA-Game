// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components\ViewPort.h"
#include "MOBA_GameGameState.h"
#include "Base.generated.h"

UCLASS()
class MOBA_GAME_API ABase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase();
	void SpawnMinion();
	FTimerHandle spawntimer;
	UClass* DefaultPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESide side_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
