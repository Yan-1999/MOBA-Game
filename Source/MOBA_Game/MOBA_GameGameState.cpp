// MOBA project group, SSE, Tonji University. Some rights reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#include "MOBA_GameGameState.h"

#include "Base.h"
#include "Hero.h"
#include "Minion.h"
#include "Monster.h"
#include "Turret.h"
#include "Table.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

constexpr size_t GROUP_NUM = 2;
constexpr size_t HERO_TYPE_NUM = 5;
constexpr size_t HERO_LEVEL_NUM = 20;

AMOBA_GameGameState::AMOBA_GameGameState()
{
	//set array number
	groups_.SetNum(GROUP_NUM);
	property_table_.SetNum(HERO_TYPE_NUM);
	for (auto& type : property_table_)
	{
		type.SetNum(HERO_LEVEL_NUM);
	}

	ability_table_.SetNum(HERO_TYPE_NUM);
	for (auto& type : ability_table_)
	{
		type.SetNum(3);
	}

	//import data tables

	ConstructorHelpers::FObjectFinder<UDataTable> PropertyTable(TEXT("DataTable'/Game/TopDownCPP/Data/property.property'"));
	ConstructorHelpers::FObjectFinder<UDataTable> ItemTable(TEXT("DataTable'/Game/TopDownCPP/Data/item.item'"));
	ConstructorHelpers::FObjectFinder<UDataTable> AbilityTable(TEXT("DataTable'/Game/TopDownCPP/Data/ability.ability'"));

	TArray<FPropertyData*>RawPropertyTable;
	PropertyTable.Object->GetAllRows<FPropertyData>(TEXT("PropertyTable"), RawPropertyTable);
	int Index = 0;
	for (auto& type : property_table_)
	{
		for (auto& level : type)
		{
			level = *(RawPropertyTable[Index++]);
		}
	}

	TArray<FAbilityData*>RawAbilityTable;
	AbilityTable.Object->GetAllRows<FAbilityData>(TEXT("PropertyTable"), RawAbilityTable);
	Index = 0;
	for (auto& type : ability_table_)
	{
		for (auto& level : type)
		{
			level = *(RawAbilityTable[Index++]);
		}
	}
}

bool AMOBA_GameGameState::Join(AActor* const pUnit, ESide side)
{
	if (side != ESide::RED && side != ESide::BLUE)
	{
		return false;
	}
	if (ABase * const pBase = Cast<ABase>(pUnit))
	{
		groups_[(uint8)side].base_ = pBase;
		return true;
	}
	if (AHero * const pHero = Cast<AHero>(pUnit))
	{
		groups_[(uint8)side].heroes_.AddUnique(pHero);
		return true;
	}
	else if (AMinion * const pMinion = Cast<AMinion>(pUnit))
	{
		groups_[(uint8)side].minions_.AddUnique(pMinion);
		return true;
	}
	else if (ATurret * const pTurret = Cast<ATurret>(pUnit))
	{
		groups_[(uint8)side].turrets_.AddUnique(pTurret);
		return true;
	}
	else
	{
		return false;
	}
}

void AMOBA_GameGameState::Leave(AActor* const pUnit)
{
	for (auto group : groups_)
	{
		if (AHero * const pHero = Cast<AHero>(pUnit))
		{
			group.heroes_.RemoveSingle(pHero);
		}
		else if (AMinion * const pMinion = Cast<AMinion>(pUnit))
		{
			group.minions_.RemoveSingle(pMinion);
		}
		else if (ATurret * const pTurret = Cast<ATurret>(pUnit))
		{
			group.turrets_.RemoveSingle(pTurret);
		}
	}
}

TArray<AActor*> AMOBA_GameGameState::GetGroup(ESide Side)
{
	TArray<AActor*>arrGruopActors;
	arrGruopActors.Append(groups_[(uint8)Side].heroes_);
	arrGruopActors.Append(groups_[(uint8)Side].minions_);
	arrGruopActors.Append(groups_[(uint8)Side].turrets_);
	return arrGruopActors;
}

TArray<AActor*> AMOBA_GameGameState::GetGroup(AActor* pUnit)
{
	ESide Side = GetSide(pUnit);
	if ((uint8)Side < GROUP_NUM)
	{
		return GetGroup(Side);
	}
	else
	{
		return TArray<AActor*>();
	}
}

ESide AMOBA_GameGameState::GetSide(AActor* pUnit)
{
	if (Cast<AMonster>(pUnit))
	{
		return ESide(2);
	}
	for (size_t i = 0; i < GROUP_NUM; i++)
	{
		if (ABase * pBase = Cast<ABase>(pUnit))
		{
			if (groups_[i].base_ == pBase)
			{
				return ESide(i);
			}
		}
		if (const AHero * const pHero = Cast<AHero>(pUnit))
		{
			if (groups_[i].heroes_.Contains(pHero))
			{
				return ESide(i);
			}
		}
		else if (const AMinion * const pMinion = Cast<AMinion>(pUnit))
		{
			if (groups_[i].minions_.Contains(pMinion))
			{
				return ESide(i);
			}
		}
		else if (const ATurret * const pTurret = Cast<ATurret>(pUnit))
		{
			if (groups_[i].turrets_.Contains(pTurret))
			{
				return ESide(i);
			}
		}
	}
	return ESide(3);
}

bool AMOBA_GameGameState::IsSameSide(AActor* pLhs, AActor* pRhs)
{
	return GetSide(pLhs) == GetSide(pRhs);
}

void AMOBA_GameGameState::Kill(AActor* pKiller, AActor* pKilled)
{
	uint8 Side = (uint8)GetSide(pKiller);
	if (Side < GROUP_NUM)
	{
		groups_[Side].score_++;
	}
}

void AMOBA_GameGameState::Kill(AActor* pKiller)
{
	uint8 Side = (uint8)GetSide(pKiller);
	GEngine->AddOnScreenDebugMessage(43, 5.0f, FColor::Yellow, TEXT("D"));
	if (Side < GROUP_NUM)
	{
		groups_[Side].score_++;
		GEngine->AddOnScreenDebugMessage(42, 5.0f, FColor::Yellow, TEXT("Score"));
	}
}

bool AMOBA_GameGameState::IsUnit(const AActor* pUnit)
{
	if ((Cast<AHero>(pUnit) || Cast<AMinion>(pUnit) || Cast<AMonster>(pUnit) || Cast<ATurret>(pUnit)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
