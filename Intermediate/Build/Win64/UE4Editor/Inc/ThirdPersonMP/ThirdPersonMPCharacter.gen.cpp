// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThirdPersonMP/ThirdPersonMPCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeThirdPersonMPCharacter() {}
// Cross Module References
	THIRDPERSONMP_API UClass* Z_Construct_UClass_AThirdPersonMPCharacter_NoRegister();
	THIRDPERSONMP_API UClass* Z_Construct_UClass_AThirdPersonMPCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_ThirdPersonMP();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FDamageEvent();
	ENGINE_API UClass* Z_Construct_UClass_AController_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	THIRDPERSONMP_API UClass* Z_Construct_UClass_AThirdPersonMPProjectile_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execHandleFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->HandleFire_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execStopFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StopFire();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execStartFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartFire();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execOnRep_CurrentHealth)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_CurrentHealth();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execTakeDamage)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_DamageTaken);
		P_GET_STRUCT_REF(FDamageEvent,Z_Param_Out_DamageEvent);
		P_GET_OBJECT(AController,Z_Param_EventInstigator);
		P_GET_OBJECT(AActor,Z_Param_DamageCauser);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->TakeDamage(Z_Param_DamageTaken,Z_Param_Out_DamageEvent,Z_Param_EventInstigator,Z_Param_DamageCauser);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execSetCurrentHealth)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_healthValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetCurrentHealth(Z_Param_healthValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execGetCurrentHealth)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetCurrentHealth();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AThirdPersonMPCharacter::execGetMaxHealth)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetMaxHealth();
		P_NATIVE_END;
	}
	static FName NAME_AThirdPersonMPCharacter_HandleFire = FName(TEXT("HandleFire"));
	void AThirdPersonMPCharacter::HandleFire()
	{
		ProcessEvent(FindFunctionChecked(NAME_AThirdPersonMPCharacter_HandleFire),NULL);
	}
	void AThirdPersonMPCharacter::StaticRegisterNativesAThirdPersonMPCharacter()
	{
		UClass* Class = AThirdPersonMPCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCurrentHealth", &AThirdPersonMPCharacter::execGetCurrentHealth },
			{ "GetMaxHealth", &AThirdPersonMPCharacter::execGetMaxHealth },
			{ "HandleFire", &AThirdPersonMPCharacter::execHandleFire },
			{ "OnRep_CurrentHealth", &AThirdPersonMPCharacter::execOnRep_CurrentHealth },
			{ "SetCurrentHealth", &AThirdPersonMPCharacter::execSetCurrentHealth },
			{ "StartFire", &AThirdPersonMPCharacter::execStartFire },
			{ "StopFire", &AThirdPersonMPCharacter::execStopFire },
			{ "TakeDamage", &AThirdPersonMPCharacter::execTakeDamage },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics
	{
		struct ThirdPersonMPCharacter_eventGetCurrentHealth_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventGetCurrentHealth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::Function_MetaDataParams[] = {
		{ "Category", "Health" },
		{ "Comment", "/** Getter for Current Health.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Getter for Current Health." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "GetCurrentHealth", nullptr, nullptr, sizeof(ThirdPersonMPCharacter_eventGetCurrentHealth_Parms), Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics
	{
		struct ThirdPersonMPCharacter_eventGetMaxHealth_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventGetMaxHealth_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::Function_MetaDataParams[] = {
		{ "Category", "Health" },
		{ "Comment", "/** Getter for Max Health.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Getter for Max Health." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "GetMaxHealth", nullptr, nullptr, sizeof(ThirdPersonMPCharacter_eventGetMaxHealth_Parms), Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Server function for spawning projectiles.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Server function for spawning projectiles." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "HandleFire", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00280CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** RepNotify for changes made to current health.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "RepNotify for changes made to current health." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "OnRep_CurrentHealth", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics
	{
		struct ThirdPersonMPCharacter_eventSetCurrentHealth_Parms
		{
			float healthValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_healthValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::NewProp_healthValue = { "healthValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventSetCurrentHealth_Parms, healthValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::NewProp_healthValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::Function_MetaDataParams[] = {
		{ "Category", "Health" },
		{ "Comment", "/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. \n\x09Should only be called on the server.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate.\n      Should only be called on the server." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "SetCurrentHealth", nullptr, nullptr, sizeof(ThirdPersonMPCharacter_eventSetCurrentHealth_Parms), Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics::Function_MetaDataParams[] = {
		{ "Category", "Gameplay" },
		{ "Comment", "/** Function for beginning weapon fire.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Function for beginning weapon fire." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "StartFire", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics::Function_MetaDataParams[] = {
		{ "Category", "Gameplay" },
		{ "Comment", "/** Function for ending weapon fire.Once this is called, the player can use StartFire again.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Function for ending weapon fire.Once this is called, the player can use StartFire again." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "StopFire", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics
	{
		struct ThirdPersonMPCharacter_eventTakeDamage_Parms
		{
			float DamageTaken;
			FDamageEvent DamageEvent;
			AController* EventInstigator;
			AActor* DamageCauser;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DamageTaken;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DamageEvent_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_DamageEvent;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_EventInstigator;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DamageCauser;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageTaken = { "DamageTaken", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventTakeDamage_Parms, DamageTaken), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageEvent_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageEvent = { "DamageEvent", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventTakeDamage_Parms, DamageEvent), Z_Construct_UScriptStruct_FDamageEvent, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageEvent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageEvent_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_EventInstigator = { "EventInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventTakeDamage_Parms, EventInstigator), Z_Construct_UClass_AController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageCauser = { "DamageCauser", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventTakeDamage_Parms, DamageCauser), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ThirdPersonMPCharacter_eventTakeDamage_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageTaken,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageEvent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_EventInstigator,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_DamageCauser,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::Function_MetaDataParams[] = {
		{ "Category", "Health" },
		{ "Comment", "/** Event for taking damage. Overridden from APawn.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Event for taking damage. Overridden from APawn." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AThirdPersonMPCharacter, nullptr, "TakeDamage", nullptr, nullptr, sizeof(ThirdPersonMPCharacter_eventTakeDamage_Parms), Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AThirdPersonMPCharacter_NoRegister()
	{
		return AThirdPersonMPCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AThirdPersonMPCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseTurnRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BaseTurnRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BaseLookUpRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BaseLookUpRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentHealth_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurrentHealth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ProjectileClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_ProjectileClass;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FireRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FireRate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AThirdPersonMPCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_ThirdPersonMP,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AThirdPersonMPCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_GetCurrentHealth, "GetCurrentHealth" }, // 2618912118
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_GetMaxHealth, "GetMaxHealth" }, // 334431962
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_HandleFire, "HandleFire" }, // 2612892867
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_OnRep_CurrentHealth, "OnRep_CurrentHealth" }, // 1447225862
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_SetCurrentHealth, "SetCurrentHealth" }, // 3190511838
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_StartFire, "StartFire" }, // 428090980
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_StopFire, "StopFire" }, // 2316921667
		{ &Z_Construct_UFunction_AThirdPersonMPCharacter_TakeDamage, "TakeDamage" }, // 521660212
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ThirdPersonMPCharacter.h" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Follow camera */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Follow camera" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FollowCamera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FollowCamera_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseTurnRate_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Base turn rate, in deg/sec. Other scaling may affect final turn rate." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseTurnRate = { "BaseTurnRate", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, BaseTurnRate), METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseTurnRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseTurnRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseLookUpRate_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Base look up/down rate, in deg/sec. Other scaling may affect final rate." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseLookUpRate = { "BaseLookUpRate", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, BaseLookUpRate), METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseLookUpRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseLookUpRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Health" },
		{ "Comment", "/** The player's maximum health. This is the highest value of their health can be. \n\x09This value is a value of the player's health, which starts at when spawned.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "The player's maximum health. This is the highest value of their health can be.\n      This value is a value of the player's health, which starts at when spawned." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0020080000010001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, MaxHealth), METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_MaxHealth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_MaxHealth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CurrentHealth_MetaData[] = {
		{ "Comment", "/** The player's current health. When reduced to 0, they are considered dead.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "The player's current health. When reduced to 0, they are considered dead." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CurrentHealth = { "CurrentHealth", "OnRep_CurrentHealth", (EPropertyFlags)0x0020080100000020, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, CurrentHealth), METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CurrentHealth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CurrentHealth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_ProjectileClass_MetaData[] = {
		{ "Category", "Gameplay|Projectile" },
		{ "Comment", "/*\n\x09???????\xcd\x81""A???\xcb\x95??\xf0\x94\xad\x8e\xcb\x82??\xe9\x82\xbd?\xdf\x82\xc9\x8eg?p?????\xcf\x90??\xc6\x8a\xd6\x90??\xc5\x82??B\n\x09HandleFire ?\xcd\x82??\xcc\x83`???[?g???A???\xc5\x8e????????B???? RPC ?\xc5\x82????A?T?[?o?[?\xc5\x82\xcc\x94??\xcb\x95??\xcc\x83X?|?[?????s???\xdc\x82??B\n\x09HandleFire ?\xc9\x82? Server ?w???q???\xdc\x82\xdc\x82??\xc4\x82??\xe9\x82\xbd?\xdf\x81""A?N???C?A???g???? HandleFire ???\xc4\x82\xd1\x8fo?????\xc6\x82????\xc6\x81""A\n\x09?\xc4\x82\xd1\x8fo?????l?b?g???[?N?o?R?\xc5\x83T?[?o?[???\xcc\x8c????\xcc\x82????L?????N?^?[?\xc9\x8c????????\xdc\x82??B\n\n\x09HandleFire ?\xc9\x82? Reliable ?w???q???\xdc\x82\xdc\x82??\xc4\x82??\xe9\x82\xbd?\xdf\x81""AHandleFire ?\xcd\x8c\xc4\x82\xd1\x8fo?????\xe9\x82\xbd?\xd1\x82?\n\x09?M???\xc5\x82??? RPC ?\xcc\x83L???[?\xc9\x94z?u?????\xdc\x82??B?\xdc\x82??A?T?[?o?[?? HandleFire ?\xf0\x90\xb3\x8f??\xc9\x8e??M?????\xc6\x83L???[?????\xed\x8f\x9c?????\xdc\x82??B\n\x09?????\xc9\x82????A?T?[?o?[?????\xcc\x8a\xd6\x90??\xc4\x82\xd1\x8fo?????m???\xc9\x8e??M???\xe9\x82\xb1?\xc6\x82??\xdb\x8f\xd8\x82????\xdc\x82??B\n\x09???????A?\xed\x8f\x9c???\xe9\x82\xb1?\xc6\x82\xc8\x82????x?\xc9\x91????? RPC ???z?u?????\xc6\x81""A?M?????\xcc\x8d??? RPC ?\xcc\x83L???[??\n\x09?I?[?o?[?t???[???\xe9\x8b\xb0?\xea\x82\xaa?????\xdc\x82??B???\xcc\x8f\xea\x8d\x87?A???[?U?[?\xcd\x8b????I?\xc9\x90\xda\x91????????????\xdc\x82??B\n\x09???\xcc\x82??\xdf\x81""A?v???C???[?????\xcc\x8a\xd6\x90????\xc4\x82\xd1\x8fo?????\xc6\x82\xcc\x82\xc5\x82????p?x?\xc9\x92??\xd3\x82????K?v???????\xdc\x82??B\n\x09*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "???????\xcd\x81""A???\xcb\x95??\xf0\x94\xad\x8e\xcb\x82??\xe9\x82\xbd?\xdf\x82\xc9\x8eg?p?????\xcf\x90??\xc6\x8a\xd6\x90??\xc5\x82??B\nHandleFire ?\xcd\x82??\xcc\x83`???[?g???A???\xc5\x8e????????B???? RPC ?\xc5\x82????A?T?[?o?[?\xc5\x82\xcc\x94??\xcb\x95??\xcc\x83X?|?[?????s???\xdc\x82??B\nHandleFire ?\xc9\x82? Server ?w???q???\xdc\x82\xdc\x82??\xc4\x82??\xe9\x82\xbd?\xdf\x81""A?N???C?A???g???? HandleFire ???\xc4\x82\xd1\x8fo?????\xc6\x82????\xc6\x81""A\n?\xc4\x82\xd1\x8fo?????l?b?g???[?N?o?R?\xc5\x83T?[?o?[???\xcc\x8c????\xcc\x82????L?????N?^?[?\xc9\x8c????????\xdc\x82??B\n\nHandleFire ?\xc9\x82? Reliable ?w???q???\xdc\x82\xdc\x82??\xc4\x82??\xe9\x82\xbd?\xdf\x81""AHandleFire ?\xcd\x8c\xc4\x82\xd1\x8fo?????\xe9\x82\xbd?\xd1\x82?\n?M???\xc5\x82??? RPC ?\xcc\x83L???[?\xc9\x94z?u?????\xdc\x82??B?\xdc\x82??A?T?[?o?[?? HandleFire ?\xf0\x90\xb3\x8f??\xc9\x8e??M?????\xc6\x83L???[?????\xed\x8f\x9c?????\xdc\x82??B\n?????\xc9\x82????A?T?[?o?[?????\xcc\x8a\xd6\x90??\xc4\x82\xd1\x8fo?????m???\xc9\x8e??M???\xe9\x82\xb1?\xc6\x82??\xdb\x8f\xd8\x82????\xdc\x82??B\n???????A?\xed\x8f\x9c???\xe9\x82\xb1?\xc6\x82\xc8\x82????x?\xc9\x91????? RPC ???z?u?????\xc6\x81""A?M?????\xcc\x8d??? RPC ?\xcc\x83L???[??\n?I?[?o?[?t???[???\xe9\x8b\xb0?\xea\x82\xaa?????\xdc\x82??B???\xcc\x8f\xea\x8d\x87?A???[?U?[?\xcd\x8b????I?\xc9\x90\xda\x91????????????\xdc\x82??B\n???\xcc\x82??\xdf\x81""A?v???C???[?????\xcc\x8a\xd6\x90????\xc4\x82\xd1\x8fo?????\xc6\x82\xcc\x82\xc5\x82????p?x?\xc9\x92??\xd3\x82????K?v???????\xdc\x82??B" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_ProjectileClass = { "ProjectileClass", nullptr, (EPropertyFlags)0x0024080000010001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, ProjectileClass), Z_Construct_UClass_AThirdPersonMPProjectile_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_ProjectileClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_ProjectileClass_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FireRate_MetaData[] = {
		{ "Category", "Gameplay" },
		{ "Comment", "/** Delay between shots in seconds.Used to control fire rate for our test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/" },
		{ "ModuleRelativePath", "ThirdPersonMPCharacter.h" },
		{ "ToolTip", "Delay between shots in seconds.Used to control fire rate for our test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FireRate = { "FireRate", nullptr, (EPropertyFlags)0x0020080000010001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AThirdPersonMPCharacter, FireRate), METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FireRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FireRate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AThirdPersonMPCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CameraBoom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FollowCamera,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseTurnRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_BaseLookUpRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_MaxHealth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_CurrentHealth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_ProjectileClass,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThirdPersonMPCharacter_Statics::NewProp_FireRate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AThirdPersonMPCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AThirdPersonMPCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AThirdPersonMPCharacter_Statics::ClassParams = {
		&AThirdPersonMPCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AThirdPersonMPCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AThirdPersonMPCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AThirdPersonMPCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AThirdPersonMPCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AThirdPersonMPCharacter, 3354393274);
	template<> THIRDPERSONMP_API UClass* StaticClass<AThirdPersonMPCharacter>()
	{
		return AThirdPersonMPCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AThirdPersonMPCharacter(Z_Construct_UClass_AThirdPersonMPCharacter, &AThirdPersonMPCharacter::StaticClass, TEXT("/Script/ThirdPersonMP"), TEXT("AThirdPersonMPCharacter"), false, nullptr, nullptr, nullptr);

	void AThirdPersonMPCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_CurrentHealth(TEXT("CurrentHealth"));

		const bool bIsValid = true
			&& Name_CurrentHealth == ClassReps[(int32)ENetFields_Private::CurrentHealth].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AThirdPersonMPCharacter"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AThirdPersonMPCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
