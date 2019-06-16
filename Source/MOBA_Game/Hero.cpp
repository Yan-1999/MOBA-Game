// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Hero.h"

#include "MOBA_GameGameState.h"
#include "MOBA_GamePlayerController.h"
#include "Minion.h"
#include "Monster.h"
#include "Table.h"
#include "Turret.h"

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

constexpr float GAIN_FREQ = 1.0f;
constexpr int GAIN_MONEY = 10;
constexpr int GAIN_EXP = 10;

//Damage Types:
UAbilityDamageType::UAbilityDamageType()
{

}

UHealType::UHealType()
{

}

//TODO:Spawn accroding to controller
AHero::AHero()
	:ad_range_(CreateDefaultSubobject<USphereComponent>(TEXT("AD Range")))
{
	//set up properties according to the controller
	if (AMOBA_GamePlayerController * MyPlayerController = Cast<AMOBA_GamePlayerController>(GetController()))
	{
		Set(MyPlayerController);
	}

	//set size of skill_
	abilities_.SetNum(3);

	//initialize ad_range_
	//ad_range_->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ad_range_->SetSphereRadius(250.0f);
	ad_range_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ad_range_->SetupAttachment(RootComponent);
	ad_range_->OnComponentBeginOverlap.AddDynamic(this, &AHero::BeginOverlap);
	ad_range_->OnComponentEndOverlap.AddDynamic(this, &AHero::EndOverlap);

}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	//set gain timer
	GetWorldTimerManager().SetTimer(gain_timier_, this, &AHero::InherentGrow, GAIN_FREQ, true);
}

void AHero::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	//ability keys
	InputComponent->BindAction("Ability_Q", IE_Pressed, this, &AHero::Ability_Q);
	InputComponent->BindAction("Ability_W", IE_Pressed, this, &AHero::Ability_W);
	InputComponent->BindAction("Ability_E", IE_Pressed, this, &AHero::Ability_E);
	//InputComponent->BindAction("Ability_R", IE_Pressed, this, &AHero::Ability_R);
}

AActor* AHero::ChooseUnit(AActor* pUnit)
{
	if ((Cast<AHero>(pUnit) || Cast<AMinion>(pUnit) || Cast<AMonster>(pUnit) || Cast<ATurret>(pUnit)) && pUnit != this)
	{
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, pUnit->GetName());
		AMOBA_GameGameState* MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
		//if (MyGameState && MyGameState->IsSameSide(this, pUnit))
		//{
		//	goto ELSE;
		//}
		chosen_unit_ = pUnit;
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

float AHero::AD(AActor* pUnit, float fAddDamageAmount = 0.0f)
{
	//GEngine->AddOnScreenDebugMessage(41, 1.0f, FColor::Blue, TEXT("ad"));
	//GEngine->AddOnScreenDebugMessage(41, 1.0f, FColor::Blue, pUnit->GetName());
	UGameplayStatics::ApplyDamage(pUnit, ad_damage_ + fAddDamageAmount, nullptr, this, UDamageType::StaticClass());
	return fAddDamageAmount;
}

void AHero::BeginOverlap(UPrimitiveComponent* OverLapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the unit is chosen and in the range, attack it.
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
	//unit is out of range, stop attacking.
	if (OtherActor == chosen_unit_ || ad_timer_.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ad_timer_);
	}
}

void AHero::ChosenUnitAD()
{
	AD(chosen_unit_);
}

float AHero::AP(FHeroAbility& Ability)
{
	float fDamageAmount = 0.0f;

	//If the ability is in cooldown or MP is not enough, AP is canceled.
	if (Ability.cur_cd_ > 0)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Black, TEXT("Cooldown!"));
		return 0.0f;
	}
	else if (cur_mp_ < Ability.mp_needed_)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Black, TEXT("No Enough MP!"));
		return 0.0f;
	}
	else
	{
		//set up ignore array
		FVector vLocation = GetActorLocation();
		TArray<AActor*>Ignores;
		if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
		{
			Ignores = MyGameState->GetGroup(this);
		}
		else
		{
			Ignores.Add(this);
		}
		if (Ability.aoe_)
		{
			UGameplayStatics::ApplyRadialDamage(this, Ability.damage_, vLocation, Ability.range_, UAbilityDamageType::StaticClass(), Ignores, this);
		}
		else
		{
			TArray<FHitResult> LinearHitResults;
			if (APlayerController * pController = Cast<APlayerController>(GetController()))
			{
				FVector vCursor = GetCursorToWorld()->GetComponentLocation() - vLocation;
				UKismetSystemLibrary::LineTraceMulti(this, vLocation, vLocation + (vCursor.GetSafeNormal2D()) * Ability.range_, TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, LinearHitResults, true, FLinearColor::Red, FLinearColor::Red);
				for (auto i : LinearHitResults)
				{
					if (i.GetActor())
					{
						GEngine->AddOnScreenDebugMessage(6, 1.0f, FColor::Blue, i.GetActor()->GetName());
						UGameplayStatics::ApplyDamage(i.GetActor(), Ability.damage_, GetController(), this, UAbilityDamageType::StaticClass());
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

//void AHero::Ability_R()
//{
//	AP(abilities_[3]);
//}

bool AHero::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (cur_hp_ < 0)
	{
		return false;
	}
	AMOBA_GameGameState* MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this));
	if (MyGameState && !(MyGameState->IsSameSide(this, DamageCauser)))
	{
		return false;
		GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Blue, TEXT("Cannot Attack"));
	}
	else
	{
		return true;
	}
}

float AHero::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fActualDamage;
	//if (ShouldTakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser))
	{
		//damage resisitance
		if (DamageEvent.DamageTypeClass == UDamageType::StaticClass())
		{
			DamageAmount *= (1 - ad_resist_ - ad_resist_add_);
			GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::Blue, TEXT("isAD"));
		}
		else if (DamageEvent.DamageTypeClass == UAbilityDamageType::StaticClass())
		{
			DamageAmount *= (1 - ap_resist_ - ap_resist_add_);
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
				if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
				{
					MyGameState->Kill(Killer, this);
				}
				Killer->Grow(drop_money_, drop_exp_);
				Killer->Score();
			}
			GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Red, TEXT("AboutDead"));
			Death();
			fActualDamage = cur_hp_;
			cur_hp_ = 0.0f;
		}
	}
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, FString::Printf(TEXT("%s:%f"), *this->GetName(), cur_hp_));
	return fActualDamage;
}

void AHero::Death()
{
	if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
	{
		GEngine->AddOnScreenDebugMessage(9, 1.0f, FColor::Red, TEXT("IsDead"));
		MyGameState->Leave(this);
		//OnDeath.Broadcast();
		if (AMOBA_GamePlayerController * MyController = Cast<AMOBA_GamePlayerController>(GetController()))
		{
			MyController->OnMyHeroDeath();
		}
	}
	Destroy();
}

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
		cur_mp_ += DeltaSeconds * (re_mp_ + addtional_mp);
		if (cur_mp_ > max_mp_)
		{
			cur_mp_ = max_mp_;
		}
	}
}

void AHero::Grow(int MoneyGain, int ExpGain)
{
	AMOBA_GamePlayerController* MyPlayerController = Cast<AMOBA_GamePlayerController>(GetController());
	money_ += MoneyGain;
	exp_ += ExpGain;
	if (exp_ >= max_exp_)
	{
		exp_ -= max_exp_;
		level_++;
		if (MyPlayerController && Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
		{
			MyPlayerController->exp_ = exp_;
			MyPlayerController->level_ = level_;
			MyPlayerController->money_ = money_;
			Set(MyPlayerController);
			GEngine->AddOnScreenDebugMessage(30, 0.5f, FColor::Blue, FString(TEXT("LEVEL:")) + FString::FromInt(level_));
		}
	}
	if (MyPlayerController)
	{
		MyPlayerController->exp_ = exp_;
		MyPlayerController->level_ = level_;
		MyPlayerController->money_ = money_;
	}
	return;
}

void AHero::InherentGrow()
{
	Grow(GAIN_MONEY, GAIN_EXP);
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
	if (cur_hp_ < 0)
	{
		Death();
	}
}

void AHero::Set(AMOBA_GamePlayerController* MyPlayerController)
{
	//if (ad_range_)
	//{
	//	GEngine->AddOnScreenDebugMessage(12, 2.0f, FColor::Magenta, TEXT("No"));
	//}
	side_ = MyPlayerController->side_;
	type_ = MyPlayerController->type_;
	level_ = MyPlayerController->level_;
	exp_ = MyPlayerController->exp_;
	money_ = MyPlayerController->money_;

	if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
	{
		MyGameState->Join(this, side_);
		for (size_t i = 0; i < 3; i++)
		{
			abilities_[i].aoe_ = MyGameState->ability_table()[(uint8)type_][i].AOE;
			abilities_[i].damage_ = MyGameState->ability_table()[(uint8)type_][i].DAMAGE;
			abilities_[i].max_cd_ = MyGameState->ability_table()[(uint8)type_][i].MAX_CD;
			abilities_[i].mp_needed_ = MyGameState->ability_table()[(uint8)type_][i].MP_NEEDED;
			abilities_[i].range_ = MyGameState->ability_table()[(uint8)type_][i].RANGE;
			abilities_[i].stablize_ = MyGameState->ability_table()[(uint8)type_][i].STABILIZE;
		}
		max_exp_ = MyGameState->property_table()[(uint8)type_][level_].EXP;
		max_hp_ = MyGameState->property_table()[(uint8)type_][level_].MAX_HP;
		max_mp_ = MyGameState->property_table()[(uint8)type_][level_].MAX_MP;
		re_hp_ = MyGameState->property_table()[(uint8)type_][level_].RE_HP;
		re_mp_ = MyGameState->property_table()[(uint8)type_][level_].RE_MP;
		ad_resist_ = MyGameState->property_table()[(uint8)type_][level_].AD_RESISIT;
		ap_resist_ = MyGameState->property_table()[(uint8)type_][level_].AP_RESISIT;
		ad_freq_ = MyGameState->property_table()[(uint8)type_][level_].AD_FREQ;
		ad_damage_ = MyGameState->property_table()[(uint8)type_][level_].AD_DAMAGE;
	}

	cur_hp_ = max_hp_;
	cur_mp_ = max_mp_;
	for (auto i : abilities_)
	{
		i.cur_cd_ = 0;
	}

	//speed
	GetCharacterMovement()->MaxWalkSpeed = speed_;

	//if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
	//{
	//	int temp = 20;
	//	{
	//		auto j = MyGameState->property_table()[0][1];
	//		FString tempstr = FString::SanitizeFloat(j.LEVEL) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.EXP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.MAX_HP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.MAX_MP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.RE_HP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.RE_MP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.AD_RESISIT) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.AP_RESISIT) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.SPEED) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.DROP_MONEY) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.DROP_EXP) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.AD_FREQ) + TEXT(" ")
	//			+ FString::SanitizeFloat(j.AD_DAMAGE);
	//		GEngine->AddOnScreenDebugMessage(temp++, 3.0f, FColor::Magenta, tempstr);
	//	}
	//}
}

void AHero::Score()
{
	if (AMOBA_GamePlayerController * MyPlayerController = Cast<AMOBA_GamePlayerController>(GetController()))
	{
		(MyPlayerController->score_)++;
	}
}

/*void AHero::Set(ESide Side, EHeroType Type, decltype(abilities_)& arrAbilities, float fMaxHp, float fMaxMp, float fReHp, float fReMp, float fAdResist, float fApResist, float fAdFreq, float fAdDamage, int Level, int Exp, int Money)
{
	//type_ = Type;
	//abilities_ = arrAbilities;
	//max_hp_ = fMaxHp;
	//max_mp_ = fMaxMp;
	//re_hp_ = fReHp;
	//re_mp_ = fReMp;
	//ad_resist_ = fAdResist;
	//ap_resist_ = fApResist;
	//ad_freq_ = fAdFreq;
	//ad_damage_ = fAdDamage;
	//level_ = Level;
	//exp_ = Exp;
	//money_ = Money;

	if (ad_range_)
	{
		GEngine->AddOnScreenDebugMessage(12, 2.0f, FColor::Magenta, TEXT("No"));
	}

	if (AMOBA_GamePlayerController * MyPlayerController = Cast<AMOBA_GamePlayerController>(GetController()))
	{
		type_ = MyPlayerController->type_;
		level_ = MyPlayerController->level_;
		exp_ = MyPlayerController->exp_;
		money_ = MyPlayerController->money_;

		if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
		{
			MyGameState->Join(this, MyPlayerController->side_);
			max_hp_ = MyGameState->property_table()[(uint8)type_][level_].MAX_HP;
			max_mp_ = MyGameState->property_table()[(uint8)type_][level_].MAX_MP;
			re_hp_ = MyGameState->property_table()[(uint8)type_][level_].RE_HP;
			re_mp_ = MyGameState->property_table()[(uint8)type_][level_].RE_MP;
			ad_resist_ = MyGameState->property_table()[(uint8)type_][level_].AD_RESISIT;
			ap_resist_ = MyGameState->property_table()[(uint8)type_][level_].AP_RESISIT;
			ad_freq_ = MyGameState->property_table()[(uint8)type_][level_].AD_FREQ;
			ad_damage_ = MyGameState->property_table()[(uint8)type_][level_].AD_DAMAGE;
		}
	}
	cur_hp_ = max_hp_;
	cur_mp_ = max_mp_;
	for (auto i : abilities_)
	{
		i.cur_cd_ = i.max_cd_;
	}

	if (AMOBA_GameGameState * MyGameState = Cast<AMOBA_GameGameState>(UGameplayStatics::GetGameState(this)))
	{
		int temp = 20;
		{
			auto j = MyGameState->property_table()[0][1];
			FString tempstr = FString::SanitizeFloat(j.LEVEL) + TEXT(" ")
				+ FString::SanitizeFloat(j.EXP) + TEXT(" ")
				+ FString::SanitizeFloat(j.MAX_HP) + TEXT(" ")
				+ FString::SanitizeFloat(j.MAX_MP) + TEXT(" ")
				+ FString::SanitizeFloat(j.RE_HP) + TEXT(" ")
				+ FString::SanitizeFloat(j.RE_MP) + TEXT(" ")
				+ FString::SanitizeFloat(j.AD_RESISIT) + TEXT(" ")
				+ FString::SanitizeFloat(j.AP_RESISIT) + TEXT(" ")
				+ FString::SanitizeFloat(j.SPEED) + TEXT(" ")
				+ FString::SanitizeFloat(j.DROP_MONEY) + TEXT(" ")
				+ FString::SanitizeFloat(j.DROP_EXP) + TEXT(" ")
				+ FString::SanitizeFloat(j.AD_FREQ) + TEXT(" ")
				+ FString::SanitizeFloat(j.AD_DAMAGE);

			GEngine->AddOnScreenDebugMessage(temp++, 3.0f, FColor::Magenta, tempstr);
		}
	}
}
*/