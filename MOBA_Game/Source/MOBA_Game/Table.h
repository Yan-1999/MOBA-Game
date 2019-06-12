// MOBA project group, SSE, Tonji University. Some rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Table.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FPropertyData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int LEVEL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int EXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float MAX_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float MAX_MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float RE_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float RE_MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AD_RESISIT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AP_RESISIT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float SPEED;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int DROP_MONEY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int DROP_EXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AD_FREQ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AD_DAMAGE;

};

USTRUCT(BlueprintType)
struct FAbilityData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") bool AOE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int RANGE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float STABILIZE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float DAMAGE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float MP_NEEDED;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float MAX_CD;

};

USTRUCT(BlueprintType)
struct FItemData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") FString NAME;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int PRICE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") int VALUE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") bool INSTANT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AD_RESIST;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AP_RESIST;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float HP_ADD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float MP_ADD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TableSetting") float AD_ADD;

};