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

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AMinion>PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/MyMinion"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}



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
	gamestate->Join(this, side_);
	AMinion* Minionup;

	AMinion* Minionmid;

	AMinion* Miniondown;
	FRotator StartRotation(ForceInit);

	StartRotation.Yaw = GetActorRotation().Yaw;

	StartRotation.Pitch = GetActorRotation().Pitch;

	StartRotation.Roll = GetActorRotation().Roll;

	FVector StartLocation = GetActorLocation();

	FTransform Transform = FTransform(StartRotation, StartLocation);


	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for (i = 0; i < 3; i++)

	{


		Minionup = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

		Minionup->type_ = MinionType::Melee;

		gamestate->Join(Minionup, gamestate->GetSide(this));

		Minionmid = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

		Minionmid->type_ = MinionType::Melee;

		gamestate->Join(Minionmid, gamestate->GetSide(this));

		Miniondown = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

		Miniondown->type_ = MinionType::Melee;

		gamestate->Join(Miniondown, gamestate->GetSide(this));

	}

	Minionup = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Minionup->type_ = MinionType::Remote;

	gamestate->Join(Minionup, gamestate->GetSide(this));

	Minionmid = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Minionmid->type_ = MinionType::Remote;

	gamestate->Join(Minionmid, gamestate->GetSide(this));

	Miniondown = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Miniondown->type_ = MinionType::Remote;

	gamestate->Join(Miniondown, gamestate->GetSide(this));

	Minionup = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Minionup->type_ = MinionType::Artillery;

	gamestate->Join(Minionup, gamestate->GetSide(this));

	Minionmid = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Minionmid->type_ = MinionType::Artillery;

	gamestate->Join(Minionmid, gamestate->GetSide(this));

	Miniondown = GetWorld()->SpawnActor<AMinion>(DefaultPawnClass, StartLocation, StartRotation, SpawnInfo);

	Miniondown->type_ = MinionType::Artillery;

	gamestate->Join(Miniondown, gamestate->GetSide(this));



}





// Called every frame

void ABase::Tick(float DeltaTime)

{

	Super::Tick(DeltaTime);

}



