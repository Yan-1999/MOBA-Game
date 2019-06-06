// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Hero.h"

#include "Minion.h"
#include "Monster.h"
#include "Turret.h"
#include "MOBA_GameGameState.h"

#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

/**Damage Types:*/
const TSubclassOf<UDamageType> ActualDamage = UDamageType::StaticClass();
const TSubclassOf<UDamageType> AbilityDamage = UAbilityDamageType::StaticClass();
const TSubclassOf<UDamageType> Healing = UHealType::StaticClass();

//TODO: Constuctor.
AHero::AHero()
	:cur_hp_(max_hp_), cur_mp_(max_mp_),
	ad_range_(CreateDefaultSubobject<USphereComponent>(TEXT("AD Range")))
{
	//set size of skill_
	abilities_.SetNum(4);

	//initialize ad_range_
	ad_range_->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ad_range_->SetSphereRadius(100.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AHero::EndOverlap);

	//speed
	GetCharacterMovement()->MaxWalkSpeed = speed_;

}

AHero::AHero(HeroType Type, decltype(abilities_) arrSkill)
	:type_(Type), abilities_(arrSkill), cur_hp_(max_hp_), cur_mp_(max_mp_),
	ad_range_(CreateDefaultSubobject<USphereComponent>(TEXT("range")))
{
	//set size of skill_
	abilities_.SetNum(4);

	//initialize ad_range_
	ad_range_->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ad_range_->SetSphereRadius(100.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AHero::EndOverlap);

	//speed
	GetCharacterMovement()->MaxWalkSpeed = speed_;
}

void AHero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{

	//ability keys
	InputComponent->BindAction("Ability_Q", IE_Pressed, this, &AHero::Ability_Q);
	InputComponent->BindAction("Ability_W", IE_Pressed, this, &AHero::Ability_W);
	InputComponent->BindAction("Ability_E", IE_Pressed, this, &AHero::Ability_E);
	InputComponent->BindAction("Ability_R", IE_Pressed, this, &AHero::Ability_R);
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
	UGameplayStatics::ApplyDamage(pUnit, fDamageAmount, nullptr, this, ActualDamage);
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
float AHero::AP(FHeroAbility& Ability)
{
	float fDamageAmount = 0.0f;
	if (Ability.cur_cd_ > 0 || cur_mp_ < Ability.mp_needed_)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Black, "Cooldown!");
		return 0.0f;
	}
	else
	{
		FVector vLocation = GetActorLocation();
		TArray<AActor*>Ignores;
		Ignores.Add(this);
		if (Ability.aoe_)
		{
			UGameplayStatics::ApplyRadialDamage(this, Ability.damage_, vLocation, Ability.range_, AbilityDamage, Ignores, this);
		}
		else
		{
			FHitResult Hit;
			TArray<FHitResult> LinearHitResults;
			if (APlayerController * pController = Cast<APlayerController>(GetController()))
			{
				pController->GetHitResultUnderCursor(ECC_Pawn, false, Hit);
				FVector vCursor = Hit.ImpactPoint - vLocation;
				UKismetSystemLibrary::LineTraceMulti(this, vLocation, vLocation + (vCursor.GetSafeNormal2D()) * Ability.range_, TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, LinearHitResults, true, FLinearColor::Red, FLinearColor::Red);
				for (auto i : LinearHitResults)
				{
					if (i.GetActor())
					{
						GEngine->AddOnScreenDebugMessage(6, 1.0f, FColor::Blue, i.GetActor()->GetName());
						UGameplayStatics::ApplyDamage(i.GetActor(), Ability.damage_, GetController(), this, AbilityDamage);
					}
				}
			}
			cur_mp_ -= Ability.mp_needed_;
			Ability.cur_cd_ = Ability.max_cd_;
		}
		return fDamageAmount;
	}
}

void AHero::Ability_Q()
{
	AP(abilities_[0]);
}

void AHero::Ability_W()
{
	AP(abilities_[1]);
}

void AHero::Ability_E()
{
	AP(abilities_[2]);
}

void AHero::Ability_R()
{
	AP(abilities_[3]);
}

//bool AHero::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	if (cur_hp_ <= 0)
//	{
//		return false;
//	}
//	return true;
//}

float AHero::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fActualDamage;
	//if (ShouldTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser))
	{
		if (DamageEvent.DamageTypeClass == ActualDamage)
		{
			DamageAmount *= (1 - ad_resist_);
			GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::Blue, TEXT("isAD"));
		}
		else if (DamageEvent.DamageTypeClass == AbilityDamage)
		{
			DamageAmount *= (1 - ap_resist_);
			GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::Blue, TEXT("isAP"));
		}
		//still alive
		if (cur_hp_ - DamageAmount >= 0.0f)
		{
			cur_hp_ -= DamageAmount;
			fActualDamage = DamageAmount;
		}
		//dead
		else
		{
			if (AHero * Killer = Cast<AHero>(DamageCauser))
			{
				Killer->Grow(drop_money_, drop_exp_);
				OnDeath.Broadcast();
			}
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
void AHero::Buy(int ItemID)
{
	items_.Add(ItemID);
}

void AHero::Sell(int ItemID)
{
	items_.RemoveSingle(ItemID);
}

//TODO: Tick function.
void AHero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Cure(DeltaSeconds);

	//renew skill cooldown
	for (auto& i : abilities_)
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

void AHero::Respawn()
{
}
