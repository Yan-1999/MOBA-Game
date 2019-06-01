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
#include "TimerManager.h"

//TODO: Constuctor.
AHero::AHero()
	:ad_range_(CreateDefaultSubobject<USphereComponent>(TEXT("AD Range")))
{
	//set size of skill_
	skill_.SetNum(4);
	//initialize ad_range_
	ad_range_->AttachTo(RootComponent);
	ad_range_->SetSphereRadius(100.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AHero::EndOverlap);
}

AHero::AHero(HeroType Type, decltype(skill_) arrSkill)
	: type_(Type), skill_(arrSkill),
	ad_range_(CreateDefaultSubobject<USphereComponent>(TEXT("range")))
{
	//set size of skill_
	skill_.SetNum(4);
	//initialize ad_range_
	ad_range_->AttachTo(RootComponent);
	ad_range_->SetSphereRadius(100.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AHero::EndOverlap);

}

AActor* AHero::ChoseUnit(AActor* pUnit)
{
	if ((Cast<AHero>(pUnit) || Cast<AMinion>(pUnit) || Cast<AMonster>(pUnit) || Cast<ATurret>(pUnit)) && pUnit != this)
	{
		chosen_unit_ = pUnit;
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, pUnit->GetName());
		if (pUnit->IsOverlappingActor(this))
		{
			GetWorldTimerManager().SetTimer(ad_timer_, this, &AHero::ChosenUnitAD, ad_freq_, true);
		}
	}
	else
	{
		chosen_unit_ = nullptr;
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, TEXT("Cancel"));
		if (ad_timer_.IsValid())
		{
			GetWorldTimerManager().ClearTimer(ad_timer_);
		}
	}
	return chosen_unit_;
}

//TODO: AD function.
float AHero::AD(AActor* pUnit, float fDamageAmount, float DegRange)
{
	UGameplayStatics::ApplyDamage(pUnit, fDamageAmount, nullptr, this, UDamageType::StaticClass());
	return fDamageAmount;
}

void AHero::BeginOverlap(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == chosen_unit_)
	{
		if (!ad_timer_.IsValid())
		{
			GetWorldTimerManager().SetTimer(ad_timer_, this, &AHero::ChosenUnitAD, ad_freq_, true);
		}
	}
}

void AHero::EndOverlap(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ad_timer_.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ad_timer_);
	}
}

void AHero::ChosenUnitAD()
{
	AD(chosen_unit_);
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

bool AHero::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
