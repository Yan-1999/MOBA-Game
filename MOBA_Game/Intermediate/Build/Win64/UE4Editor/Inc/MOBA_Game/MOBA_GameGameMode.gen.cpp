// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MOBA_Game/MOBA_GameGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMOBA_GameGameMode() {}
// Cross Module References
	MOBA_GAME_API UClass* Z_Construct_UClass_AMOBA_GameGameMode_NoRegister();
	MOBA_GAME_API UClass* Z_Construct_UClass_AMOBA_GameGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_MOBA_Game();
// End Cross Module References
	void AMOBA_GameGameMode::StaticRegisterNativesAMOBA_GameGameMode()
	{
	}
	UClass* Z_Construct_UClass_AMOBA_GameGameMode_NoRegister()
	{
		return AMOBA_GameGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMOBA_GameGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMOBA_GameGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MOBA_Game,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMOBA_GameGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MOBA_GameGameMode.h" },
		{ "ModuleRelativePath", "MOBA_GameGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMOBA_GameGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMOBA_GameGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMOBA_GameGameMode_Statics::ClassParams = {
		&AMOBA_GameGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802A8u,
		METADATA_PARAMS(Z_Construct_UClass_AMOBA_GameGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AMOBA_GameGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMOBA_GameGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMOBA_GameGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMOBA_GameGameMode, 2792414829);
	template<> MOBA_GAME_API UClass* StaticClass<AMOBA_GameGameMode>()
	{
		return AMOBA_GameGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMOBA_GameGameMode(Z_Construct_UClass_AMOBA_GameGameMode, &AMOBA_GameGameMode::StaticClass, TEXT("/Script/MOBA_Game"), TEXT("AMOBA_GameGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMOBA_GameGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
