// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MOBA_GAME_Hero_generated_h
#error "Hero.generated.h already included, missing '#pragma once' in Hero.h"
#endif
#define MOBA_GAME_Hero_generated_h

#define MOBA_Game_Source_MOBA_Game_Hero_h_15_RPC_WRAPPERS
#define MOBA_Game_Source_MOBA_Game_Hero_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define MOBA_Game_Source_MOBA_Game_Hero_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAHero(); \
	friend struct Z_Construct_UClass_AHero_Statics; \
public: \
	DECLARE_CLASS(AHero, AMOBA_GameCharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MOBA_Game"), NO_API) \
	DECLARE_SERIALIZER(AHero)


#define MOBA_Game_Source_MOBA_Game_Hero_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAHero(); \
	friend struct Z_Construct_UClass_AHero_Statics; \
public: \
	DECLARE_CLASS(AHero, AMOBA_GameCharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MOBA_Game"), NO_API) \
	DECLARE_SERIALIZER(AHero)


#define MOBA_Game_Source_MOBA_Game_Hero_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AHero(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AHero) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHero); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHero); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AHero(AHero&&); \
	NO_API AHero(const AHero&); \
public:


#define MOBA_Game_Source_MOBA_Game_Hero_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AHero(AHero&&); \
	NO_API AHero(const AHero&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHero); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHero); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AHero)


#define MOBA_Game_Source_MOBA_Game_Hero_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__max_health_() { return STRUCT_OFFSET(AHero, max_health_); } \
	FORCEINLINE static uint32 __PPO__cur_health_() { return STRUCT_OFFSET(AHero, cur_health_); } \
	FORCEINLINE static uint32 __PPO__re_health_() { return STRUCT_OFFSET(AHero, re_health_); } \
	FORCEINLINE static uint32 __PPO__max_magic_() { return STRUCT_OFFSET(AHero, max_magic_); } \
	FORCEINLINE static uint32 __PPO__cur_magic_() { return STRUCT_OFFSET(AHero, cur_magic_); } \
	FORCEINLINE static uint32 __PPO__re_magic_() { return STRUCT_OFFSET(AHero, re_magic_); } \
	FORCEINLINE static uint32 __PPO__level_() { return STRUCT_OFFSET(AHero, level_); } \
	FORCEINLINE static uint32 __PPO__exp_() { return STRUCT_OFFSET(AHero, exp_); } \
	FORCEINLINE static uint32 __PPO__money_() { return STRUCT_OFFSET(AHero, money_); }


#define MOBA_Game_Source_MOBA_Game_Hero_h_12_PROLOG
#define MOBA_Game_Source_MOBA_Game_Hero_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_PRIVATE_PROPERTY_OFFSET \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_RPC_WRAPPERS \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_INCLASS \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MOBA_Game_Source_MOBA_Game_Hero_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_PRIVATE_PROPERTY_OFFSET \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_INCLASS_NO_PURE_DECLS \
	MOBA_Game_Source_MOBA_Game_Hero_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MOBA_GAME_API UClass* StaticClass<class AHero>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MOBA_Game_Source_MOBA_Game_Hero_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
