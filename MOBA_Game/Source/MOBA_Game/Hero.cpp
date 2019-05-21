// MOBA project group, SSE, Tonji University. Some rights reserved.

#include "Hero.h"

//TODO: Constuctor.
AHero::AHero()
{

}

//TODO: Art function.
float AHero::Art()
{
	float damage = 0.0f;
	return damage;
}

//TODO: Cure function.
void AHero::Cure(float addtional_hp, float addtional_mp)
{

}

//TODO: Grow function.
void AHero::Grow(int gain)
{
	money_ += gain;
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
