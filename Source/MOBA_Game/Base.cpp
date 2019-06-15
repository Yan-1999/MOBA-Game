// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "Base.h"
#include"Minion.h"
#include"Hero.h"
#include"Engine\World.h"
#include"Engine\Classes\GameFramework\Actor.h"
#include"Classes\GameFramework\Actor.h"
#include"Kismet\GameplayStatics.h"
#include"MOBA_GameGameState.h"
#include "TimerManager.h"
#include"Components\Viewport.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABase::ABase()
{
	static ConstructorHelpers::FClassFinder<AMinion>PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/MyMinion"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(spawntimer, this, &ABase::SpawnMinion, 20.0f, true, 5.0f);

}
void ABase::SpawnMinion()
{
	int i = 0;
	UWorld* world = GetWorld();
	AMOBA_GameGameState* gamestate = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	AMinion* Minionup;
	AMinion* Minionmid;
	AMinion* Miniondown;
	FRotator StartRotation(ForceInit);
	StartRotation.Yaw = GetActorRotation().Yaw;
	FVector StartLocation = GetActorLocation();
	FTransform Transform = FTransform(StartRotation, StartLocation);

	for (i = 0; i < 3; i++)
	{
		Minionup = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		Minionup->type_ = MinionType::Melee;
		gamestate->Join(Minionup, side_);
		UGameplayStatics::FinishSpawningActor(Minionup, Transform);

		Minionmid = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		Minionup->type_ = MinionType::Melee;
		gamestate->Join(Minionmid, side_);
		UGameplayStatics::FinishSpawningActor(Minionmid, Transform);

		Miniondown = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		Minionup->type_ = MinionType::Melee;
		gamestate->Join(Miniondown, side_);
		UGameplayStatics::FinishSpawningActor(Miniondown, Transform);

	}
	Minionup = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Remote;
	gamestate->Join(Minionup, side_);
	UGameplayStatics::FinishSpawningActor(Minionup, Transform);

	Minionmid = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Remote;
	gamestate->Join(Minionmid, side_);
	UGameplayStatics::FinishSpawningActor(Minionmid, Transform);

	Miniondown = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Remote;
	gamestate->Join(Miniondown, side_);
	UGameplayStatics::FinishSpawningActor(Miniondown, Transform);

	Minionup = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Artillery;
	gamestate->Join(Minionup, side_);
	UGameplayStatics::FinishSpawningActor(Minionup, Transform);

	Minionmid = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Artillery;
	gamestate->Join(Minionmid, side_);
	UGameplayStatics::FinishSpawningActor(Minionmid, Transform);

	Miniondown = world->SpawnActorDeferred<AMinion>(DefaultPawnClass, Transform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Minionup->type_ = MinionType::Artillery;
	gamestate->Join(Miniondown, side_);
	UGameplayStatics::FinishSpawningActor(Miniondown, Transform);
}


// Called every frame
void ABase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


