// MOBA project group, SSE, Tonji University. Some rights reserved.


#include "Minion.h"
#include "Hero.h"
#include "Turret.h"
#include "Base.h"
#include "AIController.h"
#include "Perception\AIPerceptionComponent.h"
#include "Perception\AISenseConfig_Sight.h"
#include "MOBA_GameGameState.h"
#include "GameFramework/DamageType.h"
#include "TimerManager.h"
#include"Engine\Engine.h"
#include "Engine\World.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Public\NavigationSystem.h"
#include "Engine\Classes\GameFramework\Actor.h"
#include"Perception\AIPerceptionComponent.h"
#include"Perception\AIPerceptionStimuliSourceComponent.h"
#include"Perception\AIPerceptionTypes.h"
#include "Kismet\GameplayStatics.h"

//TODO: Constrcters
// Sets default values

AMinion::AMinion()

{
	PrimaryActorTick.bCanEverTick = true;

	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	Sight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sight"));

	Sight->OnTargetPerceptionUpdated.AddDynamic(this, &AMinion::PerceptionUpdated);

	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	ad_range_ = CreateDefaultSubobject<USphereComponent>(TEXT("range"));
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->SetupAttachment(RootComponent);
	


	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AMinion::BeginOverlap);

	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AMinion::EndOverlap);

	if (type_ == MinionType::Melee)
	{
		ad_range_->SetSphereRadius(2.0f);
	}

	else { ad_range_->SetSphereRadius(8.0f); }


}

AMinion::AMinion(MinionType type) :type_(type)

{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	if (GetWorld())
	{
		findwayto = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	}
}

// Called when the game starts or when spawned

void AMinion::BeginPlay()

{
	Super::BeginPlay();

}

//attack hero
void AMinion::Attack(AActor* Target, MinionType type)
{
	float damage = 0.0f;
	float attackrange = 15;
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	/*UDamageType DamageType;
	TSubclassOf<UDamageType> const ValidDamageTypeClas;
	FDamageEvent DamageEvent();*/
	if (!GameState->IsSameSide(Target, this))
	{
		FVector v1 = Target->GetActorLocation();
		FVector v2 = this->GetActorLocation();
		FVector v = v2 - v1;
		FVector w = this->GetActorForwardVector();
		float temp = FVector::DotProduct(v, w);
		float distance = FVector::Distance(Target->GetActorLocation(), this->GetActorLocation());
		float Range = acos(temp / distance);
		if (Cast<ATurret>(Target))
		{
			ATurret* turret = Cast<ATurret>(Target);

			if (type == MinionType::Melee)
			{

				if (Range < 15 && distance <= 5)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(turret, damage, nullptr, this, UDamageType::StaticClass());
				}
			}
			else if (type == MinionType::Remote)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(turret, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
			else if (type == MinionType::Artillery)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 15.0;
					UGameplayStatics::ApplyDamage(turret, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
		}
		if (Cast<AMinion>(Target))
		{
			AMinion* minion = Cast<AMinion>(Target);

			if (type == MinionType::Melee)
			{

				if (Range < 15 && distance <= 5)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(minion, damage, nullptr, this, UDamageType::StaticClass());
				}
			}
			else if (type == MinionType::Remote)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(minion, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
			else if (type == MinionType::Artillery)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 15.0;
					UGameplayStatics::ApplyDamage(minion, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
		}
		if (Cast<AHero>(Target))
		{
			AHero* hero = Cast<AHero>(Target);

			if (type == MinionType::Melee)
			{

				if (Range < 15 && distance <= 5)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(hero, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
			else if (type == MinionType::Remote)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 10.0;
					UGameplayStatics::ApplyDamage(hero, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
			else if (type == MinionType::Artillery)
			{
				if (Range < 15 && distance <= 10)
				{
					damage = 15.0;
					UGameplayStatics::ApplyDamage(hero, damage, nullptr, this, UDamageType::StaticClass());

				}
			}
		}
	}

}

//TODO:when a minion dies,the killer will gain money and exp
void AMinion::drop(AHero* Damagecauser)
{
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	if (this->cur_hp <= 0)
	{
		Damagecauser->AHero::Grow(drop_money_, drop_exp_);
		GameState->AMOBA_GameGameState::Leave(this);
		this->Destroy();
	}

}

//TO DO:health drop when a minion is attacked
float AMinion::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (cur_hp > 0 && DamageCauser != nullptr)
	{
		cur_hp -= DamageAmount;
		if (Cast<AHero>(DamageCauser) != nullptr)
		{
			Attack(DamageCauser, this->type_);
		}
	}
	return DamageAmount;
}
void AMinion::ChosenUnitAD()
{
	Attack(chosen_unit_, type_);
}
AActor* AMinion::ChoseUnit(AActor* Target)
{

	if (((Cast<ATurret>(Target) || Cast<AMinion>(Target) || Cast<AHero>(Target)) && Target != this))

	{

		chosen_unit_ = Target;

		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, Target->GetName());

		if (Target->IsOverlappingActor(this))

		{

			GetWorldTimerManager().SetTimer(attack_timer_, this, &AMinion::ChosenUnitAD, attack_freq_, true);

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

void AMinion::BeginOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMinion>(OtherActor) != nullptr || Cast<ATurret>(OtherActor) != nullptr || Cast<AMinion>(OtherActor) != nullptr)
	{
		if (!attack_timer_.IsValid())
		{
			GetWorldTimerManager().SetTimer(attack_timer_, this, &AMinion::ChosenUnitAD, attack_freq_, true);
		}
	}
}
void AMinion::EndOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (attack_timer_.IsValid())

	{

		GetWorldTimerManager().ClearTimer(attack_timer_);

	}

}

//TODO:judge whether have seen the actor and attack


// Called every frame

void AMinion::Tick(float DeltaTime)

{

	Super::Tick(DeltaTime);



}

void AMinion::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AMOBA_GameGameState* GameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	float const Distance = FVector::Dist(Actor->GetActorLocation(), GetActorLocation());
	if (!GameState->IsSameSide(Actor, this))
	{

		if (Cast<ATurret>(Actor) != nullptr)
		{

			if (findwayto && (Distance > 5.0f))
			{
				findwayto->SimpleMoveToActor(nullptr, Actor);
			}
			else
			{
				Attack(Actor, type_);
			}
		}

		else if (Cast<AMinion>(Actor) != nullptr)
		{
			if (findwayto && (Distance > 2.0f))
			{
				findwayto->SimpleMoveToActor(nullptr, Actor);
			}
			else
			{
				Attack(Actor, type_);
			}
		}
		else if (Cast<AMinion>(Actor) != nullptr)
		{
			if (findwayto && (Distance > 2.0f))
			{
				findwayto->SimpleMoveToActor(nullptr, Actor);
			}
			else
			{
				Attack(Actor, type_);
			}
		}






	}

}


