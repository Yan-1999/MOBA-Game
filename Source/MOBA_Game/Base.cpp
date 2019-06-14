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

// Sets default values
ABase::ABase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(spawntimer, this, &ABase::SpawnMinion, 120.0f, true, 5.0f);

}
void ABase::SpawnMinion()
{
	int i = 0;
	UWorld* world = GetWorld();
	AMOBA_GameGameState* gamestate = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	AMinion* Minionup;
	AMinion* Minionmid;
	AMinion* Miniondown;
	for (i = 0; i < 3; i++)
	{
		Minionup = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
		Minionup->type_ = MinionType::Melee;
		//gamestate->Join(Minionmid, gamestate->IsInSide(this));
		Minionmid = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
		Minionmid->type_ = MinionType::Melee;
		//gamestate->Join(Minionmid, gamestate->IsInSide(this));
		Miniondown = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
		Miniondown->type_ = MinionType::Melee;
		//gamestate->Join(Miniondown, gamestate->IsInSide(this));
	}
	Minionup = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Minionup->type_ = MinionType::Remote;
	//gamestate->Join(Minionup, gamestate->IsInSide(this));
	Minionmid = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Minionmid->type_ = MinionType::Remote;
	//gamestate->Join(Minionmid, gamestate->IsInSide(this));
	Miniondown = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Miniondown->type_ = MinionType::Remote;
	//gamestate->Join(Miniondown, gamestate->IsInSide(this));
	Minionup = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Minionup->type_ = MinionType::Artillery;
	//gamestate->Join(Minionup, gamestate->IsInSide(this));
	Minionmid = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Minionmid->type_ = MinionType::Artillery;
	//gamestate->Join(Minionmid, gamestate->IsInSide(this));
	Miniondown = world->UWorld::SpawnActor<AMinion>(AMinion::StaticClass(), GetActorLocation(), GetActorRotation());
	Miniondown->type_ = MinionType::Artillery;
	//gamestate->Join(Miniondown, gamestate->IsInSide(this));

}


// Called every frame
void ABase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


