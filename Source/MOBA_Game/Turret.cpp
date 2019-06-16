// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "Turret.h"
#include "Hero.h"
#include "Minion.h"
#include"MOBA_GameGameState.h"
#include"AIController.h"
#include "TimerManager.h"
#include "GameFramework/DamageType.h"
#include"Perception\AIPerceptionComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurret::ATurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ad_range_ = CreateDefaultSubobject<USphereComponent>(TEXT("range"));
	ad_range_->SetSphereRadius(10.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->SetupAttachment(RootComponent);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &ATurret::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &ATurret::EndOverlap);
}
ATurret::ATurret(FIndex index)
{

}

//TODO:Turrent's AD
void ATurret::Attack(AActor* Target)
{
	float damage = 0.0f;
	float attackrange = 15;
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	UDamageType DamageType;
	TSubclassOf<UDamageType> const ValidDamageTypeClass/* = DamageType? DamageType : TSubclassOf<UDamageType>(UDamageType::StaticClass())*/;
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	if (GameState && (Cast<AHero>(Target) || Cast<AMinion>(Target)) && (!GameState->IsSameSide(Target, this)))
	{

		FVector vDelta = GetActorLocation() - Target->GetActorLocation(), vFwd = GetActorForwardVector();
		float fDistance = vDelta.Size();
		float fRange = acos(FVector::DotProduct(vDelta, vFwd) / fDistance);
		if (fRange < 15 && fDistance <= 5)
		{
			Target->TakeDamage(damage, DamageEvent, nullptr, this);
		}
	}
}
//TODO:Turret takedamage
float ATurret::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (cur_hp_ > 0)
	{
		cur_hp_ -= DamageAmount;
	}
	else  if (cur_hp_ <= 0)
	{
		if (AHero * Killer = Cast<AHero>(DamageCauser))
		{
			Killer->Grow(drop_money_, drop_exp_);
		}
		if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
		{
			MyGameState->Leave(this);
		}
		Destroy();
	}
	float ActualDamage = DamageAmount;
	return  ActualDamage;
}
void ATurret::ChosenUnitAD()
{
	Attack(chosen_unit_);
}
AActor* ATurret::ChoseUnit(AActor* Target)
{

	if ((Cast<AHero>(Target) || Cast<AMinion>(Target) && Target != this))

	{

		chosen_unit_ = Target;

		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, Target->GetName());

		if (Target->IsOverlappingActor(this))

		{

			GetWorldTimerManager().SetTimer(attack_timer_, this, &ATurret::ChosenUnitAD, attack_freq_, true);

		}

	}

	else

	{

		chosen_unit_ = nullptr;

		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, TEXT("Cancel"));

		if (attack_timer_.IsValid())

		{

			GetWorldTimerManager().ClearTimer(attack_timer_);

		}

	}

	return chosen_unit_;

}



void ATurret::BeginOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{

		if (!attack_timer_.IsValid())

		{

			GetWorldTimerManager().SetTimer(attack_timer_, this, &ATurret::ChosenUnitAD, attack_freq_, true);

		}
	}

}

void ATurret::EndOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (attack_timer_.IsValid())

	{

		GetWorldTimerManager().ClearTimer(attack_timer_);

	}
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
