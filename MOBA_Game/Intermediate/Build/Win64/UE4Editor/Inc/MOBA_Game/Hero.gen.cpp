// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MOBA_Game/Hero.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHero() {}
// Cross Module References
	MOBA_GAME_API UClass* Z_Construct_UClass_AHero_NoRegister();
	MOBA_GAME_API UClass* Z_Construct_UClass_AHero();
	MOBA_GAME_API UClass* Z_Construct_UClass_AMOBA_GameCharacter();
	UPackage* Z_Construct_UPackage__Script_MOBA_Game();
// End Cross Module References
	void AHero::StaticRegisterNativesAHero()
	{
	}
	UClass* Z_Construct_UClass_AHero_NoRegister()
	{
		return AHero::StaticClass();
	}
	struct Z_Construct_UClass_AHero_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_money__MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_money_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_exp__MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_exp_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_level__MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_level_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_re_magic__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_re_magic_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_cur_magic__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_cur_magic_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_max_magic__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_max_magic_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_re_health__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_re_health_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_cur_health__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_cur_health_;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_max_health__MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_max_health_;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AHero_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AMOBA_GameCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MOBA_Game,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Hero.h" },
		{ "ModuleRelativePath", "Hero.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_money__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|Money" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Money owned by hero. Minus value is INVAILD." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_money_ = { "money_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, money_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_money__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_money__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_exp__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|Level" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "EXP of Hero. Used to determine hero's level. Minus value is INVAILD." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_exp_ = { "exp_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, exp_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_exp__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_exp__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_level__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|Level" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Level of Hero. Used to determine hero's max HP & MP." },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_level_ = { "level_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, level_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_level__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_level__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_re_magic__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Speed of MP Recovery PER SECOND. Can be minus." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_re_magic_ = { "re_magic_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, re_magic_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_re_magic__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_re_magic__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_cur_magic__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Hero's current MP value. Minus value or above max is INVAILD." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_cur_magic_ = { "cur_magic_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, cur_magic_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_cur_magic__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_cur_magic__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_max_magic__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Hero's max MP value. Used as an upper bound of current magic power." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_max_magic_ = { "max_magic_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, max_magic_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_max_magic__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_max_magic__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_re_health__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Speed of HP Recovery PER SECOND. Can be minus." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_re_health_ = { "re_health_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, re_health_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_re_health__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_re_health__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_cur_health__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Hero's current HP value. Zero value means death. Minus value or above max is INVAILD." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_cur_health_ = { "cur_health_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, cur_health_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_cur_health__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_cur_health__MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AHero_Statics::NewProp_max_health__MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Properties|HP&MP" },
		{ "ModuleRelativePath", "Hero.h" },
		{ "ToolTip", "Upper bound of hero's current health. Zero value or below is INVAILD." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AHero_Statics::NewProp_max_health_ = { "max_health_", nullptr, (EPropertyFlags)0x0040000000020005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AHero, max_health_), METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::NewProp_max_health__MetaData, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::NewProp_max_health__MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AHero_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_money_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_exp_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_level_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_re_magic_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_cur_magic_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_max_magic_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_re_health_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_cur_health_,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AHero_Statics::NewProp_max_health_,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AHero_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AHero>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AHero_Statics::ClassParams = {
		&AHero::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AHero_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AHero_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AHero_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AHero()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AHero_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AHero, 495563303);
	template<> MOBA_GAME_API UClass* StaticClass<AHero>()
	{
		return AHero::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AHero(Z_Construct_UClass_AHero, &AHero::StaticClass, TEXT("/Script/MOBA_Game"), TEXT("AHero"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AHero);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
