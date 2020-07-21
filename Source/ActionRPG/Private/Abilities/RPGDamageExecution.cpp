// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Abilities/RPGDamageExecution.h"
#include "Abilities/RPGAttributeSet.h"
#include "AbilitySystemComponent.h"

struct RPGDamageStatics
{
	//defensive of target
	DECLARE_ATTRIBUTE_CAPTUREDEF(GlobalDamageReductionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistancePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistancePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdResistancePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistancePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosResistancePercent);
	//offensive of source
	DECLARE_ATTRIBUTE_CAPTUREDEF(GlobalDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamagePercent);
	//Conditional
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MeleeDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ProjectileDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RangedDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MinionDamagePercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageOverTimeDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AreaDamagePercent);
	//Conversion
	//Physical Conversion
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalToFireConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalToColdConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalToLightningConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalToChaosConversionPercent);
	//Fire Conversion
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireToPhysicalConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireToColdConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireToLightningConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireToChaosConversionPercent);
	//Cold Conversion
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdToPhysicalConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdToFireConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdToLightningConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdToChaosConversionPercent);
	//Lightning Conversion
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningToPhysicalConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningToFireConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningToColdConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningToChaosConversionPercent);
	//Chaos Conversion
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosToPhysicalConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosToFireConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosToColdConversionPercent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosToLightningConversionPercent);
	//Weapon Damage
	//DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamageSwordPercent);
	//flat damage numbers
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	RPGDamageStatics()
	{
		//Defensive target attributes, not snapshotted - false
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, GlobalDamageReductionPercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosResistancePercent, Target, false);

		//Source Offensive Attriutes, snapshotted so it takes the value on launch, not on hit
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, GlobalDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, CriticalHitDamagePercent, Source, true);
		//Conditional
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, MagicDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, MeleeDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AttackDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, SpellDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ProjectileDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, RangedDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, MinionDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DamageOverTimeDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AreaDamagePercent, Source, true);
		//Conversion
		//Physical Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalToFireConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalToColdConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalToLightningConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalToChaosConversionPercent, Source, true);
		//Fire Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireToPhysicalConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireToColdConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireToLightningConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireToChaosConversionPercent, Source, true);
		//Cold Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdToPhysicalConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdToFireConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdToLightningConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdToChaosConversionPercent, Source, true);
		//Lightning Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningToPhysicalConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningToFireConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningToColdConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningToChaosConversionPercent, Source, true);
		//Chaos Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosToPhysicalConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosToFireConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosToColdConversionPercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosToLightningConversionPercent, Source, true);
		//Weapon Damage
		//DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, WeaponDamageSwordPercent, Source, true);
		//Source Damage Attributes, snapshotted so it takes the value on launch, not on hit
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosDamage, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, Damage, Source, true);
	}
};

static const RPGDamageStatics& DamageStatics()
{
	static RPGDamageStatics DmgStatics;
	return DmgStatics;
}

URPGDamageExecution::URPGDamageExecution()
{
	//Target defensive
#define CAP(Name) \
	RelevantAttributesToCapture.Add(DamageStatics().Name##Def)

	CAP(GlobalDamageReductionPercent);
	CAP(PhysicalResistancePercent);
	CAP(FireResistancePercent);
	CAP(ColdResistancePercent);
	CAP(LightningResistancePercent);
	CAP(ChaosResistancePercent);
	
	//Source Offensive
	CAP(GlobalDamagePercent);
	CAP(PhysicalDamagePercent);
	CAP(FireDamagePercent);
	CAP(ColdDamagePercent);
	CAP(LightningDamagePercent);
	CAP(ChaosDamagePercent);
	CAP(CriticalHitDamagePercent);
	//Conditional
	CAP(MagicDamagePercent);
	CAP(MeleeDamagePercent);
	CAP(AttackDamagePercent);
	CAP(SpellDamagePercent);
	CAP(ProjectileDamagePercent);
	CAP(RangedDamagePercent);
	CAP(MinionDamagePercent);
	CAP(DamageOverTimeDamage);
	CAP(AreaDamagePercent);
	//Conversion
	//Physical Conversion
	CAP(PhysicalToFireConversionPercent);
	CAP(PhysicalToColdConversionPercent);
	CAP(PhysicalToLightningConversionPercent);
	CAP(PhysicalToChaosConversionPercent);
	//Fire Conversion
	CAP(FireToPhysicalConversionPercent);
	CAP(FireToColdConversionPercent);
	CAP(FireToLightningConversionPercent);
	CAP(FireToChaosConversionPercent);
	//Cold Conversion
	CAP(ColdToPhysicalConversionPercent);
	CAP(ColdToFireConversionPercent);
	CAP(ColdToLightningConversionPercent);
	CAP(ColdToChaosConversionPercent);
	//Lightning Conversion
	CAP(LightningToPhysicalConversionPercent);
	CAP(LightningToFireConversionPercent);
	CAP(LightningToColdConversionPercent);
	CAP(LightningToChaosConversionPercent);
	//Chaos Conversion
	CAP(ChaosToPhysicalConversionPercent);
	CAP(ChaosToFireConversionPercent);
	CAP(ChaosToColdConversionPercent);
	CAP(ChaosToLightningConversionPercent);
	//Weapon Damage
	//CAP(WeaponDamageSwordPercent);
	//Source Damage 
	CAP(PhysicalDamage);
	CAP(FireDamage);
	CAP(ColdDamage);
	CAP(LightningDamage);
	CAP(ChaosDamage);

	CAP(Damage);
}

void URPGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayTagContainer SpecTags;
	Spec.GetAllAssetTags(SpecTags);

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	/******************************************************************************
	Conditional Damage
	*******************************************************************************/
#define CAPTURE(Name) \
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Name##Def, EvaluationParameters, Name)

#define CONVERSION(name) \
	float name##ConversionPercent = 0.f; \
	CAPTURE(name##ConversionPercent);

#define TAGCHECK(VarName, TagName) \
	float VarName = 1.f; \
	if (SpecTags.HasTag(FGameplayTag::RequestGameplayTag(FName(TagName)))) \
	{ \
		CAPTURE(VarName); \
	}

	/**********************************************************************************************************
	Defensive properties
	**********************************************************************************************************/
	float GlobalDamageReductionPercent = 0.f;
	CAPTURE(GlobalDamageReductionPercent);

	float PhysicalResistancePercent = 0.f;
	CAPTURE(PhysicalResistancePercent);

	float FireResistancePercent= 0.f;
	CAPTURE(FireResistancePercent);

	float ColdResistancePercent = 0.f;
	CAPTURE(ColdResistancePercent);

	float LightningResistancePercent = 0.f;
	CAPTURE(LightningResistancePercent);

	float ChaosResistancePercent = 0.f;
	CAPTURE(ChaosResistancePercent);

	/**********************************************************************************************************
	Offensive properties
	**********************************************************************************************************/
	float GlobalDamagePercent= 1.f;
	CAPTURE(GlobalDamagePercent);

	float PhysicalDamagePercent= 1.f;
	CAPTURE(PhysicalDamagePercent);

	float FireDamagePercent= 1.f;
	CAPTURE(FireDamagePercent);

	float ColdDamagePercent = 1.f;
	CAPTURE(ColdDamagePercent);

	float LightningDamagePercent = 1.f;
	CAPTURE(LightningDamagePercent);

	float ChaosDamagePercent = 1.f;
	CAPTURE(ChaosDamagePercent);

	float CriticalHitDamagePercent = 1.f;
	CAPTURE(CriticalHitDamagePercent);

	/**********************************************************************************************************
	Conditional Damage
	**********************************************************************************************************/

	//Will Only be applied if ability is tagged with damage over time

	TAGCHECK(MagicDamagePercent, "Ability.Damage.Magic");
	TAGCHECK(MeleeDamagePercent, "Ability.Damage.Melee");
	TAGCHECK(AttackDamagePercent, "Ability.Type.Attack");
	TAGCHECK(SpellDamagePercent, "Ability.Type.Spell");
	TAGCHECK(ProjectileDamagePercent, "Ability.Damage.Projectile");
	TAGCHECK(RangedDamagePercent, "Ability.Damage.Ranged");
	TAGCHECK(MinionDamagePercent, "Ability.Damage.Minion");
	TAGCHECK(DamageOverTimeDamage, "Ability.Damage.DamageOverTime");
	TAGCHECK(AreaDamagePercent, "Ability.Damage.Area");

	/**********************************************************************************************************
	Elemental Conversion
	**********************************************************************************************************/

	CONVERSION(PhysicalToFire);
	CONVERSION(PhysicalToCold);
	CONVERSION(PhysicalToLightning);
	CONVERSION(PhysicalToChaos);

	CONVERSION(FireToPhysical);
	CONVERSION(FireToCold);
	CONVERSION(FireToLightning);
	CONVERSION(FireToChaos);

	CONVERSION(ColdToPhysical);
	CONVERSION(ColdToFire);
	CONVERSION(ColdToLightning);
	CONVERSION(ColdToChaos);

	CONVERSION(LightningToPhysical);
	CONVERSION(LightningToFire);
	CONVERSION(LightningToCold);
	CONVERSION(LightningToChaos);

	CONVERSION(ChaosToPhysical);
	CONVERSION(ChaosToFire);
	CONVERSION(ChaosToCold);
	CONVERSION(ChaosToLightning);

	/**********************************************************************************************************
	Misc properties, like duration/area of effect
	**********************************************************************************************************/
	
	/**********************************************************************************************************
	Result properties, don't modify these directly
	**********************************************************************************************************/

	float PhysicalDamage= 0.f;
	CAPTURE(PhysicalDamage);

	float FireDamage= 0.f;
	CAPTURE(FireDamage);

	float ColdDamage = 0.f;
	CAPTURE(ColdDamage);

	float LightningDamage = 0.f;
	CAPTURE(LightningDamage);

	float ChaosDamage = 0.f;
	CAPTURE(ChaosDamage);

	/**********************************************************************************************************
	WeaponDamage Calculations
	**********************************************************************************************************/

	//Base skill damage + Base weapon damage if weapon is of applicable type (attack vs spell)* %Weaponscaling * %extradamagewithweapon


	/**********************************************************************************************************
	Conversion Calculations
	**********************************************************************************************************/

#define CONVERTELEMENT(A, B) \
	float Temp##To##B##From##A = A##Damage * A##To##B##ConversionPercent; \
	A##Damage = A##Damage * (1 - A##To##B##ConversionPercent); \
	B##Damage += Temp##To##B##From##A;

	/*
	We start with converting everything in order like this everything->physical->fire->cold->lightning->chaos
	this means that elements have the reverse priority in which one will be favored if damage id convered back and forth between multiple things
	Ex. if you have conversion of every type to every other type somehow, it will all end up as chaos damage
	*/
	CONVERTELEMENT(Fire, Physical);
	CONVERTELEMENT(Cold, Physical);
	CONVERTELEMENT(Lightning, Physical);
	CONVERTELEMENT(Chaos, Physical);

	CONVERTELEMENT(Physical, Fire);
	CONVERTELEMENT(Cold, Fire);
	CONVERTELEMENT(Lightning, Fire);
	CONVERTELEMENT(Chaos, Fire);

	CONVERTELEMENT(Physical, Cold);
	CONVERTELEMENT(Fire, Cold);
	CONVERTELEMENT(Lightning, Cold);
	CONVERTELEMENT(Chaos, Cold);

	CONVERTELEMENT(Physical, Lightning);
	CONVERTELEMENT(Fire, Lightning);
	CONVERTELEMENT(Cold, Lightning);
	CONVERTELEMENT(Chaos, Lightning);

	CONVERTELEMENT(Physical, Chaos);
	CONVERTELEMENT(Fire, Chaos);
	CONVERTELEMENT(Cold, Chaos);
	CONVERTELEMENT(Lightning, Chaos);

	/**********************************************************************************************************
	Final Calculations
	**********************************************************************************************************/

	float PhysicalDamageDone = PhysicalDamage * PhysicalDamagePercent * (1 - PhysicalResistancePercent);
	float FireDamageDone = FireDamage * FireDamagePercent  * (1 - FireResistancePercent);
	float ColdDamageDone = ColdDamage * ColdDamagePercent * (1 - ColdResistancePercent);
	float LightningDamageDone = LightningDamage * LightningDamagePercent * (1 - LightningResistancePercent);
	float ChaosDamageDone = ChaosDamage * ChaosDamagePercent * (1 - ChaosResistancePercent);
	float TotalDamageDone = PhysicalDamageDone + FireDamageDone + ColdDamageDone + LightningDamageDone + ChaosDamageDone;
	TotalDamageDone *= GlobalDamagePercent * (1 - GlobalDamageReductionPercent);
	TotalDamageDone *= MagicDamagePercent;
	TotalDamageDone *= MeleeDamagePercent;
	TotalDamageDone *= AttackDamagePercent;
	TotalDamageDone *= SpellDamagePercent;
	TotalDamageDone *= ProjectileDamagePercent;
	TotalDamageDone *= RangedDamagePercent;
	TotalDamageDone *= MinionDamagePercent;
	TotalDamageDone *= DamageOverTimeDamage;
	TotalDamageDone *= AreaDamagePercent;
	if (false/*it's a critical hit*/)
	{
		TotalDamageDone *= CriticalHitDamagePercent;
	}
	if (TotalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, TotalDamageDone));
	}
}