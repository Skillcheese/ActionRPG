// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Abilities/RPGAttributeSet.h"
#include "Abilities/RPGAbilitySystemComponent.h"
#include "RPGCharacterBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

URPGAttributeSet::URPGAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, Mana(0.f)
	, MaxMana(0.f)
	, ManaRegen(1.f)
	, MoveSpeed(1.0f)
	, Damage(0.0f)

	//Defensive
	, GlobalDamageReductionPercent(0.0f)
	, PhysicalResistancePercent(0.0f)
	, FireResistancePercent(0.0f)
	, ColdResistancePercent(0.0f)
	, LightningResistancePercent(0.0f)
	, ChaosResistancePercent(0.0f)
	//Offensive
	, GlobalDamagePercent(1.f)
	, PhysicalDamagePercent(1.f)
	, FireDamagePercent(1.f)
	, ColdDamagePercent(1.f)
	, LightningDamagePercent(1.f)
	, ChaosDamagePercent(1.f)
	//Results
	, PhysicalDamage(0.0f)
	, FireDamage(0.0f)
	, ColdDamage(0.0f)
	, LightningDamage(0.0f)
	, ChaosDamage(0.0f)
	//Misc
	, Duration(1.f)
	, AreaOfEffect(1.f)
{
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGAttributeSet, Health);
	DOREPLIFETIME(URPGAttributeSet, MaxHealth);
	DOREPLIFETIME(URPGAttributeSet, Mana);
	DOREPLIFETIME(URPGAttributeSet, MaxMana);
	DOREPLIFETIME(URPGAttributeSet, ManaRegen);
	DOREPLIFETIME(URPGAttributeSet, MoveSpeed);

	//Offensive
	DOREPLIFETIME(URPGAttributeSet, GlobalDamageReductionPercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, FireResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, ColdResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, LightningResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosResistancePercent);
	//Defensive
	DOREPLIFETIME(URPGAttributeSet, GlobalDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, FireDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, ColdDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, LightningDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosDamagePercent);
	//Results
	DOREPLIFETIME(URPGAttributeSet, PhysicalDamage);
	DOREPLIFETIME(URPGAttributeSet, FireDamage);
	DOREPLIFETIME(URPGAttributeSet, ColdDamage);
	DOREPLIFETIME(URPGAttributeSet, LightningDamage);
	DOREPLIFETIME(URPGAttributeSet, ChaosDamage);
	//Misc
	DOREPLIFETIME(URPGAttributeSet, Duration);
	DOREPLIFETIME(URPGAttributeSet, AreaOfEffect);
}

void URPGAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health);
}

void URPGAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth);
}

void URPGAttributeSet::OnRep_Mana()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Mana);
}

void URPGAttributeSet::OnRep_MaxMana()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxMana);
}

void URPGAttributeSet::OnRep_ManaRegen()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ManaRegen);
}

void URPGAttributeSet::OnRep_MoveSpeed()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MoveSpeed);
}

void URPGAttributeSet::OnRep_GlobalDamageReductionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, GlobalDamageReductionPercent);
}

void URPGAttributeSet::OnRep_PhysicalResistancePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalResistancePercent);
}

void URPGAttributeSet::OnRep_FireResistancePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireResistancePercent);
}

void URPGAttributeSet::OnRep_ColdResistancePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdResistancePercent);
}

void URPGAttributeSet::OnRep_LightningResistancePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningResistancePercent);
}

void URPGAttributeSet::OnRep_ChaosResistancePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosResistancePercent);
}

void URPGAttributeSet::OnRep_GlobalDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, GlobalDamagePercent);
}

void URPGAttributeSet::OnRep_PhysicalDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalDamagePercent);
}

void URPGAttributeSet::OnRep_FireDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireDamagePercent);
}

void URPGAttributeSet::OnRep_ColdDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdDamagePercent);
}

void URPGAttributeSet::OnRep_LightningDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningDamagePercent);
}

void URPGAttributeSet::OnRep_ChaosDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosDamagePercent);
}

void URPGAttributeSet::OnRep_PhysicalDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalDamage);
}

void URPGAttributeSet::OnRep_FireDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireDamage);
}

void URPGAttributeSet::OnRep_ColdDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdDamage);
}

void URPGAttributeSet::OnRep_LightningDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningDamage);
}

void URPGAttributeSet::OnRep_ChaosDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosDamage);
}

void URPGAttributeSet::OnRep_Duration()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Duration);
}

void URPGAttributeSet::OnRep_AreaOfEffect()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AreaOfEffect);
}

void URPGAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ARPGCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ARPGCharacterBase>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Get the Source actor
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ARPGCharacterBase* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			if (SourceController)
			{
				SourceCharacter = Cast<ARPGCharacterBase>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ARPGCharacterBase>(SourceActor);
			}

			// Set the causer actor based on context if it's set
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// Try to extract a hit result
		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// This is proper damage
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

				// Call for all health changes
				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp mana
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		if (TargetCharacter)
		{
			// Call for all movespeed changes
			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
		}
	}
}
