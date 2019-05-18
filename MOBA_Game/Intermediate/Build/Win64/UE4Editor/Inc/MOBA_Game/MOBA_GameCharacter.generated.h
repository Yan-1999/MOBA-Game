// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MOBA_GAME_MOBA_GameCharacter_generated_h
#error "MOBA_GameCharacter.generated.h already included, missing '#pragma once' in MOBA_GameCharacter.h"
#endif
#define MOBA_GAME_MOBA_GameCharacter_generated_h

#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_RPC_WRAPPERS
#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMOBA_GameCharacter(); \
	friend struct Z_Construct_UClass_AMOBA_GameCharacter_Statics; \
public: \
	DECLARE_CLASS(AMOBA_GameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MOBA_Game"), NO_API) \
	DECLARE_SERIALIZER(AMOBA_GameCharacter)


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAMOBA_GameCharacter(); \
	friend struct Z_Construct_UClass_AMOBA_GameCharacter_Statics; \
public: \
	DECLARE_CLASS(AMOBA_GameCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MOBA_Game"), NO_API) \
	DECLARE_SERIALIZER(AMOBA_GameCharacter)


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMOBA_GameCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMOBA_GameCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMOBA_GameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMOBA_GameCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMOBA_GameCharacter(AMOBA_GameCharacter&&); \
	NO_API AMOBA_GameCharacter(const AMOBA_GameCharacter&); \
public:


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMOBA_GameCharacter(AMOBA_GameCharacter&&); \
	NO_API AMOBA_GameCharacter(const AMOBA_GameCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMOBA_GameCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMOBA_GameCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMOBA_GameCharacter)


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TopDownCameraComponent() { return STRUCT_OFFSET(AMOBA_GameCharacter, TopDownCameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AMOBA_GameCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__CursorToWorld() { return STRUCT_OFFSET(AMOBA_GameCharacter, CursorToWorld); }


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_9_PROLOG
#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_RPC_WRAPPERS \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_INCLASS \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_INCLASS_NO_PURE_DECLS \
	MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MOBA_GAME_API UClass* StaticClass<class AMOBA_GameCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MOBA_Game_Source_MOBA_Game_MOBA_GameCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
