// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MOBA_Game/MOBA_GamePlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMOBA_GamePlayerController() {}
// Cross Module References
	MOBA_GAME_API UClass* Z_Construct_UClass_AMOBA_GamePlayerController_NoRegister();
	MOBA_GAME_API UClass* Z_Construct_UClass_AMOBA_GamePlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_MOBA_Game();
// End Cross Module References
	void AMOBA_GamePlayerController::StaticRegisterNativesAMOBA_GamePlayerController()
	{
	}
	UClass* Z_Construct_UClass_AMOBA_GamePlayerController_NoRegister()
	{
		return AMOBA_GamePlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AMOBA_GamePlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMOBA_GamePlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_MOBA_Game,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMOBA_GamePlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MOBA_GamePlayerController.h" },
		{ "ModuleRelativePath", "MOBA_GamePlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMOBA_GamePlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMOBA_GamePlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMOBA_GamePlayerController_Statics::ClassParams = {
		&AMOBA_GamePlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AMOBA_GamePlayerController_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AMOBA_GamePlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMOBA_GamePlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMOBA_GamePlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMOBA_GamePlayerController, 2042829871);
	template<> MOBA_GAME_API UClass* StaticClass<AMOBA_GamePlayerController>()
	{
		return AMOBA_GamePlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMOBA_GamePlayerController(Z_Construct_UClass_AMOBA_GamePlayerController, &AMOBA_GamePlayerController::StaticClass, TEXT("/Script/MOBA_Game"), TEXT("AMOBA_GamePlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMOBA_GamePlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
