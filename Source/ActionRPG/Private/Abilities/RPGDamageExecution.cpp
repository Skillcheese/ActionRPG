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
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalToFireConversionPercent);

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
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, RnagedDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, MinionDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DamageOverTimeDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, AreaDamagePercent, Source, true);
		//Conversion
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalToFireConversionPercent, Source, true);

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
	CAP(PhysicalToFireConversionPercent);

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