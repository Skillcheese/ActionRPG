// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGBlueprintLibrary.h"
#include "ActionRPGLoadingScreen.h"


URPGBlueprintLibrary::URPGBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URPGBlueprintLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	IActionRPGLoadingScreenModule& LoadingScreenModule = IActionRPGLoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void URPGBlueprintLibrary::StopLoadingScreen()
{
	IActionRPGLoadingScreenModule& LoadingScreenModule = IActionRPGLoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

bool URPGBlueprintLibrary::IsInEditor()
{
	return GIsEditor;
}

bool URPGBlueprintLibrary::EqualEqual_RPGItemSlot(const FRPGItemSlot& A, const FRPGItemSlot& B)
{
	return A == B;
}

bool URPGBlueprintLibrary::NotEqual_RPGItemSlot(const FRPGItemSlot& A, const FRPGItemSlot& B)
{
	return A != B;
}

bool URPGBlueprintLibrary::IsValidItemSlot(const FRPGItemSlot& ItemSlot)
{
	return ItemSlot.IsValid();
}

bool URPGBlueprintLibrary::DoesEffectContainerSpecHaveEffects(const FRPGGameplayEffectContainerSpec& ContainerSpec)
{
	return ContainerSpec.HasValidEffects();
}

bool URPGBlueprintLibrary::DoesEffectContainerSpecHaveTargets(const FRPGGameplayEffectContainerSpec& ContainerSpec)
{
	return ContainerSpec.HasValidTargets();
}

FRPGGameplayEffectContainerSpec URPGBlueprintLibrary::AddTargetsToEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec, const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
	FRPGGameplayEffectContainerSpec NewSpec = ContainerSpec;
	NewSpec.AddTargets(HitResults, TargetActors);
	return NewSpec;
}

TArray<FActiveGameplayEffectHandle> URPGBlueprintLibrary::ApplyExternalEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;

	// Iterate list of gameplay effects
	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		if (SpecHandle.IsValid())
		{
			// If effect is valid, iterate list of targets and apply to all
			for (TSharedPtr<FGameplayAbilityTargetData> Data : ContainerSpec.TargetData.Data)
			{
				AllEffects.Append(Data->ApplyGameplayEffectSpec(*SpecHandle.Data.Get()));
			}
		}
	}
	return AllEffects;
}

FString URPGBlueprintLibrary::MyGameplayEffectToString(const TSubclassOf<UGameplayEffect> Effect, int32 Level)
{
	FString DamageTypesString = "";
	FString TagsString = "Tags: ";
	UGameplayEffect* DefaultEffectObject = Effect.GetDefaultObject();
	
	bool isDamageOverTime = DefaultEffectObject->InheritableGameplayEffectTags.Added.HasTag(FGameplayTag::RequestGameplayTag(FName("Ability.Damage.DamageOverTime")));
	if (isDamageOverTime)
	{
		TagsString.Append("Damage Over Time");
	}
	TArray<FString> DamageNames = TArray<FString>();
	DamageNames.Add("PhysicalDamage");
	DamageNames.Add("FireDamage");
	DamageNames.Add("ColdDamage");
	DamageNames.Add("LightningDamage");
	DamageNames.Add("ChaosDamage");
	for (FGameplayEffectExecutionDefinition Execution : DefaultEffectObject->Executions)
	{
		for (FGameplayEffectExecutionScopedModifierInfo Modifier : Execution.CalculationModifiers)
		{
			FString name = Modifier.CapturedAttribute.AttributeToCapture.AttributeName;
			if (DamageNames.Contains(name))
			{
				if (name == "PhysicalDamage")
				{
					DamageTypesString.Append("Physical");
				}
				else if (name == "FireDamage")
				{
					DamageTypesString.Append("Fire");
				}
				else if (name == "ColdDamage")
				{
					DamageTypesString.Append("Cold");
				}
				else if (name == "LightningDamage")
				{
					DamageTypesString.Append("lightning");
				}
				else if (name == "ChaosDamage")
				{
					DamageTypesString.Append("Chaos");
				}

				float OutMagnitude = 0.f;
				if (Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level, OutMagnitude))
				{
					DamageTypesString.Append(" ");
					DamageTypesString.Append(FString::SanitizeFloat(OutMagnitude));
					DamageTypesString.Append("\n");
				}
				else
				{
					DamageTypesString.Append("Failed to get magnitude");
				}
			}
		}
	}
	return TagsString + "\n" + DamageTypesString;
}
