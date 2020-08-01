// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Abilities/RPGAttributeSet.h"
#include "Abilities/RPGAbilitySystemComponent.h"
#include "RPGCharacterBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

URPGAttributeSet::URPGAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, HealthRegen(0.f)
	, Mana(0.f)
	, MaxMana(0.f)
	, ManaRegen(1.f)
	, Stamina(0.f)
	, MaxStamina(0.f)
	, StaminaRegen(1.f)
	, MoveSpeed(1.0f)
	, Damage(0.0f)

	/**********************************************************************************************************
	Defensive properties
	**********************************************************************************************************/
	, GlobalDamageReductionPercent(0.0f)
	, PhysicalResistancePercent(0.0f)
	, FireResistancePercent(0.0f)
	, ColdResistancePercent(0.0f)
	, LightningResistancePercent(0.0f)
	, ChaosResistancePercent(0.0f)
	, DodgeEffectiveness(0.0f)
	, DodgeDamageReductionPercent(0.0f)
	, BlockEffectiveness(0.0f)
	, BlockDamageReductionPercent(0.0f)
	//Offensive
	, GlobalDamagePercent(1.f)
	, PhysicalDamagePercent(1.f)
	, FireDamagePercent(1.f)
	, ColdDamagePercent(1.f)
	, LightningDamagePercent(1.f)
	, ChaosDamagePercent(1.f)
	, CriticalHitDamagePercent(1.f)
	//Conditional
	, MagicDamagePercent(1.f)
	, MeleeDamagePercent(1.f)
	, AttackDamagePercent(1.f)
	, SpellDamagePercent(1.f)
	, ProjectileDamagePercent(1.f)
	, RangedDamagePercent(1.f)
	, MinionDamagePercent(1.f)
	, DamageOverTimeDamage(1.f)
	, AreaDamagePercent(1.f)
	//Conversion
	//Physcial Conversion
	, PhysicalToFireConversionPercent(0.f)
	, PhysicalToColdConversionPercent(0.f)
	, PhysicalToLightningConversionPercent(0.f)
	, PhysicalToChaosConversionPercent(0.f)
	//Fire Conversion
	, FireToPhysicalConversionPercent(0.f)
	, FireToColdConversionPercent(0.f)
	, FireToLightningConversionPercent(0.f)
	, FireToChaosConversionPercent(0.f)
	//Cold Conversion
	, ColdToPhysicalConversionPercent(0.f)
	, ColdToFireConversionPercent(0.f)
	, ColdToLightningConversionPercent(0.f)
	, ColdToChaosConversionPercent(0.f)
	//Lightning Conversion
	, LightningToPhysicalConversionPercent(0.f)
	, LightningToFireConversionPercent(0.f)
	, LightningToColdConversionPercent(0.f)
	, LightningToChaosConversionPercent(0.f)
	//Chaos Conversion
	, ChaosToPhysicalConversionPercent(0.f)
	, ChaosToFireConversionPercent(0.f)
	, ChaosToColdConversionPercent(0.f)
	, ChaosToLightningConversionPercent(0.f)
	//Weapon Damage
	//, WeaponDamageSwordPercent(1.f)
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
	DOREPLIFETIME(URPGAttributeSet, HealthRegen);
	DOREPLIFETIME(URPGAttributeSet, Mana);
	DOREPLIFETIME(URPGAttributeSet, MaxMana);
	DOREPLIFETIME(URPGAttributeSet, ManaRegen);
	DOREPLIFETIME(URPGAttributeSet, Stamina);
	DOREPLIFETIME(URPGAttributeSet, MaxStamina);
	DOREPLIFETIME(URPGAttributeSet, StaminaRegen);
	DOREPLIFETIME(URPGAttributeSet, MoveSpeed);

	/**********************************************************************************************************
	Defensive properties
	**********************************************************************************************************/
	DOREPLIFETIME(URPGAttributeSet, GlobalDamageReductionPercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, FireResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, ColdResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, LightningResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosResistancePercent);
	DOREPLIFETIME(URPGAttributeSet, DodgeEffectiveness);
	DOREPLIFETIME(URPGAttributeSet, DodgeDamageReductionPercent);
	DOREPLIFETIME(URPGAttributeSet, BlockEffectiveness);
	DOREPLIFETIME(URPGAttributeSet, BlockDamageReductionPercent);

	/**********************************************************************************************************
	Offensive properties
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, GlobalDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, FireDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, ColdDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, LightningDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, CriticalHitDamagePercent);

	/**********************************************************************************************************
	Conditional Damage
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, MagicDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, MeleeDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, AttackDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, SpellDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, ProjectileDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, RangedDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, MinionDamagePercent);
	DOREPLIFETIME(URPGAttributeSet, DamageOverTimeDamage);
	DOREPLIFETIME(URPGAttributeSet, AreaDamagePercent);

	/**********************************************************************************************************
	Elemental Conversion
	**********************************************************************************************************/
	
	/**********************************************************************************************************
	Physical Conversion
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, PhysicalToFireConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalToColdConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalToLightningConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, PhysicalToChaosConversionPercent);

	/**********************************************************************************************************
	Fire Conversion
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, FireToPhysicalConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, FireToColdConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, FireToLightningConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, FireToChaosConversionPercent);

	/**********************************************************************************************************
	Cold Conversion
	**********************************************************************************************************/
	
	DOREPLIFETIME(URPGAttributeSet, ColdToPhysicalConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ColdToFireConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ColdToLightningConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ColdToChaosConversionPercent);

	/**********************************************************************************************************
	Lightning Conversion
	**********************************************************************************************************/
	
	DOREPLIFETIME(URPGAttributeSet, LightningToPhysicalConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, LightningToFireConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, LightningToColdConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, LightningToChaosConversionPercent);

	/**********************************************************************************************************
	Chaos Conversion
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, ChaosToPhysicalConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosToFireConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosToColdConversionPercent);
	DOREPLIFETIME(URPGAttributeSet, ChaosToLightningConversionPercent);

	/**********************************************************************************************************
	Weapon damage properties
	**********************************************************************************************************/

	//DOREPLIFETIME(URPGAttributeSet, WeaponDamageSwordPercent);

	/**********************************************************************************************************
	Misc properties, like duration/area of effect
	**********************************************************************************************************/
	DOREPLIFETIME(URPGAttributeSet, Duration);
	DOREPLIFETIME(URPGAttributeSet, AreaOfEffect);

	/**********************************************************************************************************
	Result properties, don't modify these directly
	**********************************************************************************************************/

	DOREPLIFETIME(URPGAttributeSet, PhysicalDamage);
	DOREPLIFETIME(URPGAttributeSet, FireDamage);
	DOREPLIFETIME(URPGAttributeSet, ColdDamage);
	DOREPLIFETIME(URPGAttributeSet, LightningDamage);
	DOREPLIFETIME(URPGAttributeSet, ChaosDamage);
}

void URPGAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health);
}

void URPGAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth);
}

void URPGAttributeSet::OnRep_HealthRegen()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, HealthRegen);
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

void URPGAttributeSet::OnRep_Stamina()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Stamina);
}

void URPGAttributeSet::OnRep_MaxStamina()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxStamina);
}

void URPGAttributeSet::OnRep_StaminaRegen()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, StaminaRegen);
}

void URPGAttributeSet::OnRep_MoveSpeed()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MoveSpeed);
}

/**********************************************************************************************************
Defensive properties
**********************************************************************************************************/
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

void URPGAttributeSet::OnRep_DodgeEffectiveness()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DodgeEffectiveness);
}

void URPGAttributeSet::OnRep_DodgeDamageReductionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DodgeDamageReductionPercent);
}

void URPGAttributeSet::OnRep_BlockEffectiveness()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, BlockEffectiveness);
}

void URPGAttributeSet::OnRep_BlockDamageReductionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, BlockDamageReductionPercent);
}

/**********************************************************************************************************
Offensive properties
**********************************************************************************************************/

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

void URPGAttributeSet::OnRep_CriticalHitDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalHitDamagePercent);
}

/**********************************************************************************************************
Conditional Damage
**********************************************************************************************************/

void URPGAttributeSet::OnRep_MagicDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MagicDamagePercent);
}

void URPGAttributeSet::OnRep_MeleeDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MeleeDamagePercent);
}

void URPGAttributeSet::OnRep_AttackDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AttackDamagePercent);
}

void URPGAttributeSet::OnRep_SpellDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, SpellDamagePercent);
}

void URPGAttributeSet::OnRep_ProjectileDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ProjectileDamagePercent);
}

void URPGAttributeSet::OnRep_RangedDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, RangedDamagePercent);
}

void URPGAttributeSet::OnRep_MinionDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MinionDamagePercent);
}

void URPGAttributeSet::OnRep_DamageOverTimeDamage()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DamageOverTimeDamage);
}

void URPGAttributeSet::OnRep_AreaDamagePercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AreaDamagePercent);
}

/**********************************************************************************************************
Elemental Conversion
**********************************************************************************************************/

/**********************************************************************************************************
Physical Conversion
**********************************************************************************************************/

void URPGAttributeSet::OnRep_PhysicalToFireConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalToFireConversionPercent);
}

void URPGAttributeSet::OnRep_PhysicalToColdConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalToColdConversionPercent);
}

void URPGAttributeSet::OnRep_PhysicalToLightningConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalToLightningConversionPercent);
}

void URPGAttributeSet::OnRep_PhysicalToChaosConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalToChaosConversionPercent);
}

/**********************************************************************************************************
Fire Conversion
**********************************************************************************************************/

void URPGAttributeSet::OnRep_FireToPhysicalConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireToPhysicalConversionPercent);
}

void URPGAttributeSet::OnRep_FireToColdConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireToColdConversionPercent);
}

void URPGAttributeSet::OnRep_FireToLightningConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireToLightningConversionPercent);
}

void URPGAttributeSet::OnRep_FireToChaosConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireToChaosConversionPercent);
}

/**********************************************************************************************************
Cold Conversion
**********************************************************************************************************/

void URPGAttributeSet::OnRep_ColdToPhysicalConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdToPhysicalConversionPercent);
}

void URPGAttributeSet::OnRep_ColdToFireConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdToFireConversionPercent);
}

void URPGAttributeSet::OnRep_ColdToLightningConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdToLightningConversionPercent);
}

void URPGAttributeSet::OnRep_ColdToChaosConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ColdToChaosConversionPercent);
}

/**********************************************************************************************************
Lightning Conversion
**********************************************************************************************************/

void URPGAttributeSet::OnRep_LightningToPhysicalConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningToPhysicalConversionPercent);
}

void URPGAttributeSet::OnRep_LightningToFireConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningToFireConversionPercent);
}

void URPGAttributeSet::OnRep_LightningToColdConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningToColdConversionPercent);
}

void URPGAttributeSet::OnRep_LightningToChaosConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningToChaosConversionPercent);
}

/**********************************************************************************************************
Chaos Conversion
**********************************************************************************************************/

void URPGAttributeSet::OnRep_ChaosToPhysicalConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosToPhysicalConversionPercent);
}

void URPGAttributeSet::OnRep_ChaosToFireConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosToFireConversionPercent);
}

void URPGAttributeSet::OnRep_ChaosToColdConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosToColdConversionPercent);
}

void URPGAttributeSet::OnRep_ChaosToLightningConversionPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ChaosToLightningConversionPercent);
}

/**********************************************************************************************************
Weapon damage properties
**********************************************************************************************************/

/*
void URPGAttributeSet::WeaponDamageSwordPercent()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, WeaponDamageSwordPercent);
}
*/

/**********************************************************************************************************
Misc properties, like duration/area of effect
**********************************************************************************************************/

void URPGAttributeSet::OnRep_Duration()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Duration);
}

void URPGAttributeSet::OnRep_AreaOfEffect()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AreaOfEffect);
}

/**********************************************************************************************************
Result properties, don't modify these directly
**********************************************************************************************************/

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
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
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
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		// Clamp Stamina
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

		if (TargetCharacter)
		{
			TargetCharacter->HandleStaminaChanged(DeltaValue, SourceTags);
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
