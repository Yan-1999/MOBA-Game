// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "Monster.h"
#include"Hero.h"
#include"MOBA_GameGameState.h"
#include "GameFramework/DamageType.h"
#include"Kismet\GameplayStatics.h"
#include"NavigationSystem.h"


// Sets default values
AMonster::AMonster()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMonster::AMonster(MonsterType type) :type_(type)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AMonster::Spawn()
{

}
//when a monster is attacked,it attacks.
void AMonster::Attack(AActor* Target)
{
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	UDamageType DamageType;
	TSubclassOf<UDamageType> const ValidDamageTypeClass/* = DamageType? DamageType : TSubclassOf<UDamageType>(UDamageType::StaticClass())*/;
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	float damage = 250.0f;
	FVector v1 = Target->GetActorLocation();
	FVector v2 = this->GetActorLocation();
	distance = FVector::Distance(v1, v2);
	if (Cast<AHero>(Target) != nullptr && distance < 5.0f)
	{
		Target->TakeDamage(damage, DamageEvent, nullptr, this);
	}
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = DamageAmount;
	if (cur_hp_ > 0 && DamageCauser != nullptr && DamageAmount != 0)
	{
		cur_hp_ -= DamageAmount;
		Attack(DamageCauser);
	}
	else if (cur_hp_ <= 0)
	{
		MonsterDrop(Cast<AHero>(DamageCauser));
	}
	return DamageAmount;
}

void AMonster::MonsterDrop(AHero* DamageCauser)
{
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	DamageCauser->AHero::Grow(drop_money_, drop_exp_);
	GameState->AMOBA_GameGameState::Leave(this);
	this->Destroy();
}


// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

