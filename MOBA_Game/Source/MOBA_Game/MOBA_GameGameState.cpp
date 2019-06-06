// MOBA project group, SSE, Tonji University. Some rights reserved.

// Edited by MOBA project group, SSE, Tonji University. Some rights reserved.

#include "MOBA_GameGameState.h"

#include "Hero.h"
#include "Minion.h"
#include "Monster.h"
#include "Turret.h"

constexpr uint8 GROUPNUM = 2;

AMOBA_GameGameState::AMOBA_GameGameState()
{
	groups_.SetNum(GROUPNUM);
}

bool AMOBA_GameGameState::Join(AActor* const pUnit, Side side)
{
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

Side AMOBA_GameGameState::IsInSide(const AActor* const pUnit)
{
	if (Cast<AMonster>(pUnit))
	{
		return Side(2);
	}
	for (size_t i = 0; i < GROUPNUM; i++)
	{
		if (const AHero * const pHero = Cast<AHero>(pUnit))
		{
			if (groups_[i].heroes_.Contains(pHero))
			{
				return Side(i);
			}
		}
		else if (const AMinion * const pMinion = Cast<AMinion>(pUnit))
		{
			if (groups_[i].minions_.Contains(pMinion))
			{
				return Side(i);
			}
		}
		else if (const ATurret * const pTurret = Cast<ATurret>(pUnit))
		{
			if (groups_[i].turrets_.Contains(pTurret))
			{
				return Side(i);
			}
		}
	}
	return Side(3);
}

bool AMOBA_GameGameState::IsSameSide(const AActor* const pLhs, const AActor* const pRhs)
{
	return IsInSide(pLhs) == IsInSide(pRhs);
}
