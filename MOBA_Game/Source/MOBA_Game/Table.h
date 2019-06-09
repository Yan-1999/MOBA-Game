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

	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int LEVEL;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int EXP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float MAX_HP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float MAX_MP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float RE_HP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float RE_MP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AD_RESISIT;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AP_RESISIT;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float SPEED;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int DROP_MONEY;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int DROP_EXP;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AD_FREQ;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AD_DAMAGE;

};

USTRUCT(BlueprintType)
struct FAbilityData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") bool AOE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int RANGE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float STABILIZE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float DAMAGE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float MP_NEEDED;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float MAX_CD;

};

USTRUCT(BlueprintType)
struct FItemData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") FString NAME;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int PRICE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") int VALUE;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") bool INSTANT;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AD_RESIST;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AP_RESIST;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float HP_ADD;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float MP_ADD;
	UPROPERTY(BlueprintReadOnly, Category = "TableSetting") float AD_ADD;

};