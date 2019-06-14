/// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

enum class ESide :uint8;

enum class ELane :uint8
{
	UP UMETA(DisplayName = "up"),
	MID UMETA(DisplayName = "mid"),
	DOWN UMETA(DisplayName = "down")
};

USTRUCT(BlueprintType)
struct FIndex
{
	GENERATED_USTRUCT_BODY()

public:
	ELane road;
	int order;
	ESide side;
};

UCLASS()
class MOBA_GAME_API ATurret : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret();

	void Attack(AActor* Target);

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = Collision)
		class USphereComponent* ad_range_;

	UFUNCTION()
		float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION()
	AActor * ChoseUnit(AActor * Target);

	UFUNCTION()
		void BeginOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* OverLapComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void  ChosenUnitAD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))

		AActor* chosen_unit_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Attack", meta = (AllowPrivateAccess = "true"))

		float attack_freq_;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))

		FTimerHandle attack_timer_;
	FIndex index_;
	//turret's health
	const float max_hp_ = 6000;
	float cur_hp_ = 6000;
	const float damage_ = 300;
	const float attackrange_ = 300;
	const int drop_money_ = 300;
	const int drop_exp_ = 300;
};