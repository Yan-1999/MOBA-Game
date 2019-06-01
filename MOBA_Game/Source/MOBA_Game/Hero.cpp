// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Hero.h"
#include "Minion.h"
#include "Monster.h"
#include "Turret.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

//TODO: Constuctor.
AHero::AHero()
	:range_(CreateDefaultSubobject<USphereComponent>(TEXT("range")))
{
	range_->AttachTo(RootComponent);
	range_->SetSphereRadius(200.0f);
	range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnHit);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

}

AHero::AHero(HeroType Type, decltype(skill_) arrSkill)
	: type_(Type), skill_(arrSkill), range_(CreateDefaultSubobject<USphereComponent>(TEXT("range")))

{
	range_->AttachTo(RootComponent);
	range_->SetSphereRadius(100.0f);
	range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnHit);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

}

float DegAngle(const FVector& Lhs, const FVector& Rhs)
{
	return UKismetMathLibrary::DegAcos(FVector::DotProduct(Lhs, Rhs) / (Lhs.Size() * Rhs.Size()));
}

AActor* AHero::ChoseUnit(AActor* pUnit)
{
	if (Cast<AHero>(pUnit) || Cast<AMinion>(pUnit) || Cast<AMonster>(pUnit) || Cast<ATurret>(pUnit))
	{
		chosen_unit_ = pUnit;
	}
	else
	{
		chosen_unit_ = nullptr;
	}
	return chosen_unit_;
}

//TODO: AD function.
auto AHero::AD(AActor* pUnit, float fDamageAmount, float DegRange)
{
	FVector vFacing = GetActorForwardVector(), vLocationDiff = pUnit->GetActorLocation() - GetActorLocation();
	if (DegAngle(vFacing, vLocationDiff) <= DegRange)
	{
		UGameplayStatics::ApplyDamage(pUnit, fDamageAmount, nullptr, this, UDamageType::StaticClass());
		return fDamageAmount;
	}
	return 0.0f;
}

void AHero::OnHit(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor == chosen_unit_)
	{
		AD(OtherActor);
	}
}

//TODO: Art function.
auto AHero::AP(FHeroSkill& Skill)
{
	float fDamageAmount = 0.0f;
	if (Skill.cur_cd_ > 0)
	{
		return -1.0f;
	}
	Skill.cur_cd_ = Skill.max_cd_;
	return fDamageAmount;

}

bool AHero::ShouldTakeDamage
(
	float Damage,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	if (cur_hp_ <= 0)
	{
		return false;
	}
	return true;
}

float AHero::TakeDamage
(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	float fActualDamage;
	if (ShouldTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser))
	{
		if (cur_hp_ - DamageAmount > 0.0f)
		{
			cur_hp_ -= DamageAmount;
			fActualDamage = DamageAmount;
		}
		else
		{
			fActualDamage = cur_hp_;
			cur_hp_ = 0.0f;
		}
	}
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, FString::Printf(TEXT("%s:%f"), *this->GetName(), cur_hp_));
	return fActualDamage;
}

//TODO: Cure function.
void AHero::Cure(float DeltaSeconds, float addtional_hp = 0.0f, float addtional_mp = 0.0f)
{
	if (cur_hp_ < max_hp_)
	{
		cur_hp_ += DeltaSeconds * (re_hp_ + addtional_hp);
		if (cur_hp_ > max_hp_)
		{
			cur_hp_ = max_hp_;
		}
	}
	if (cur_mp_ < max_mp_)
	{
		cur_hp_ += DeltaSeconds * (re_hp_ + addtional_hp);
		if (cur_mp_ > max_mp_)
		{
			cur_mp_ = max_mp_;
		}
	}
}

void AHero::Grow(int MoneyGain, int ExpGain)
{
	money_ += MoneyGain;
	exp_ += ExpGain;
	return;
}

//TODO: Buy function.
void AHero::Buy()
{

}

//TODO: Tick function.
void AHero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Cure(DeltaSeconds);

	//renew skill cooldown
	for (auto& i : skill_)
	{
		if (i.cur_cd_ - DeltaSeconds > 0.0f)
		{
			i.cur_cd_ -= DeltaSeconds;
		}
		else
		{
			i.cur_cd_ = 0.0f;
		}
	}
}
