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
#define CheckTag(Name) \
	DefaultEffectObject->InheritableGameplayEffectTags.Added.HasTag(FGameplayTag::RequestGameplayTag(Name))

	FString DamageTypesString = "";
	FString TagsString = "";
	UGameplayEffect* DefaultEffectObject = Effect.GetDefaultObject();
	TArray<FGameplayEffectExecutionDefinition> Executions = DefaultEffectObject->Executions;
	bool isDamageOverTime = CheckTag(FName("Ability.Damage.DamageOverTime"));
	bool isMagic = CheckTag(FName("Ability.Damage.Magic"));
	bool isMelee = CheckTag(FName("Ability.Damage.Melee"));
	bool isRanged = CheckTag(FName("Ability.Damage.Ranged"));
	bool isProjectile = CheckTag(FName("Ability.Damage.Projectile"));
	bool isMinion = CheckTag(FName("Ability.Damage.Minion"));

	bool putComma = false;
#define CommaCheck if (putComma) \
{ \
 TagsString.Append(", "); \
} \
putComma = true; 
	
	if (isDamageOverTime)
	{
		CommaCheck
		TagsString.Append("Damage Over Time");
	}
	if (isMagic)
	{
		CommaCheck
		TagsString.Append("Magic");
	}
	if (isMelee)
	{
		CommaCheck
		TagsString.Append("Melee");
	}
	if (isRanged)
	{
		CommaCheck
		TagsString.Append("Ranged");
	}
	if (isProjectile)
	{
		CommaCheck
		TagsString.Append("Projectile");
	}
	if (isMinion)
	{
		CommaCheck
		TagsString.Append("Minion");
	}
	CommaCheck
	TArray<FString> DamageNames = TArray<FString>();
	DamageNames.Add("PhysicalDamage");
	DamageNames.Add("FireDamage");
	DamageNames.Add("ColdDamage");
	DamageNames.Add("LightningDamage");
	DamageNames.Add("ChaosDamage");
	for (int i = 0; i < Executions.Num(); i++)
	{
		FGameplayEffectExecutionDefinition Execution = Executions[i];
		TArray<FGameplayEffectExecutionScopedModifierInfo> Modifiers = Execution.CalculationModifiers;
		for (int j = 0; j < Modifiers.Num(); j++)
		{
			FGameplayEffectExecutionScopedModifierInfo Modifier = Modifiers[j];
			FString name = Modifier.CapturedAttribute.AttributeToCapture.AttributeName;
			if (DamageNames.Contains(name))
			{
				if (DamageTypesString != "")
				{
					DamageTypesString.Append(", ");
				}

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
				}
				else
				{
					DamageTypesString.Append("Failed to get magnitude");
				}
			}
		}
	}
	if (TagsString == "" && DamageTypesString == "")
	{
		return "";
	}
	return TagsString + "" + DamageTypesString;
}

FString URPGBlueprintLibrary::MyGameplayAbilityToString(const TSubclassOf<URPGGameplayAbility> Ability, int32 Level)
{
	FString r = "Ability Tags: ";
	URPGGameplayAbility* AbilityObject = Ability.GetDefaultObject();
	FGameplayTagContainer tags = AbilityObject->AbilityTags;
	for (int i = 0; i < tags.Num(); i++)
	{
		FGameplayTag Tag = tags.GetByIndex(i);
		FString add = TagToString(Tag);
		r += add;
		if (i < tags.Num() - 1 && add != "")
		{
			r += ", ";
		}
	}
	r += "\nDamage Tags: ";
	TMap<FGameplayTag, FRPGGameplayEffectContainer> EffectContainerMap = TMap<FGameplayTag, FRPGGameplayEffectContainer>();
	EffectContainerMap = AbilityObject->EffectContainerMap;
	TArray<FGameplayTag> Tags = TArray<FGameplayTag>();
	EffectContainerMap.GetKeys(Tags);
	for (int i = 0; i < Tags.Num(); i++)
	{
		FGameplayTag Tag = Tags[i];
		FRPGGameplayEffectContainer* EffectContainer = EffectContainerMap.Find(Tag);
		TArray<TSubclassOf<UGameplayEffect>> EffectArray = EffectContainer->TargetGameplayEffectClasses;
		for (int j = 0; j < EffectArray.Num(); j++)
		{
			TSubclassOf<UGameplayEffect> EffectClass = EffectArray[j];
			r += MyGameplayEffectToString(EffectClass, Level);
		}
	}
	return r;
}

FString URPGBlueprintLibrary::TagToString(FGameplayTag Tag)
{
	FString tag = Tag.ToString();
	if (tag == "Ability.Skill" || tag == "Ability.Melee")
	{
		return "";
	}
	else if (tag == "Ability.Type.Attack")
	{
		return "Attack";
	}
	else if (tag == "Ability.Type.Spell")
	{
		return "Spell";
	}
	else if (tag == "Ability.Skill.OnFootstep")
	{
		return "Footstep";
	}
	return Tag.ToString();
}
