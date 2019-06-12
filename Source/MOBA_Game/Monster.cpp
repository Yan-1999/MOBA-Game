// MOBA project group, SSE, Tonji University. Some rights reserved.





#include "Monster.h"



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



float AMonster::attack()

{

	float damage = 0.0f;

	return damage;

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