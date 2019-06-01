// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Minion.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"

//TODO: Constrcters
// Sets default values
AMinion::AMinion()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMinion::AMinion(MinionType type) :type_(type)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//TODO: AD function
auto AMinion::AD()
{
	float damage = 0.0f;
	return damage;
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// //Called to bind functionality to input
//void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	//Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void AWeaponActor::ActiveAttack()
{
	bCanAttack = true;
	if (WeaponCollision != nullptr) //Collision activated
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AWeaponActor::DeactiveAttack() //Collision deactivated
{
	bCanAttack = false;
	if (WeaponCollision != nullptr)
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AWeaponActor::OnHit
(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (bCanAttack && OtherActor != this) 
	{
		//IBeAttackInterface* AC = Cast<IBeAttackInterface>(OtherActor);
		//if (AC != nullptr)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.0f, nullptr, this, UDamageType::StaticClass()); 
		}
	}

}
