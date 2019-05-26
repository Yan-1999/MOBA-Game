// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Hero.h"
#include <utility>

//TODO: Constuctor.
AHero::AHero()
{

}

AHero::AHero(HeroType type, FHeroSkill skill)
	:type_(type), skill_(skill)
{

}

//TODO: AD function.
auto AHero::AD()
{
	float damage = 0.0f;
	return damage;

}

//TODO: Art function.
auto AHero::AP(FHeroSkill skill)
{
	float damage = 0.0f;
	return damage;

}

//TODO: Cure function.
void AHero::Cure(float addtional_hp, float addtional_mp)
{

}

void AHero::Grow(decltype(drop_) gain)
{
	money_ += gain.first;
	exp_ += gain.second;
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

}
