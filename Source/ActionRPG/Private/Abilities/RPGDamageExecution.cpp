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
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageOverTimeDamage);

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
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DamageOverTimeDamage, Source, true);

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
	CAP(DamageOverTimeDamage);

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
	DAMAGE OVER TIME
	*******************************************************************************/
	//Will Only be applied if ability is tagged with damage over time
	float DamageOverTimeDamage = 1.f;
#define CAPTURE(Name) \
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().Name##Def, EvaluationParameters, Name)

	if (SpecTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Ability.Damage.DamageOverTime"))))
	{
		CAPTURE(DamageOverTimeDamage);
	}

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

	float PhysicalDamageDone = PhysicalDamage * PhysicalDamagePercent * (1 - PhysicalResistancePercent);
	float FireDamageDone = FireDamage * FireDamagePercent  * (1 - FireResistancePercent);
	float ColdDamageDone = ColdDamage * ColdDamagePercent * (1 - ColdResistancePercent);
	float LightningDamageDone = LightningDamage * LightningDamagePercent * (1 - LightningResistancePercent);
	float ChaosDamageDone = ChaosDamage * ChaosDamagePercent * (1 - ChaosResistancePercent);
	float TotalDamageDone = PhysicalDamageDone + FireDamageDone + ColdDamageDone + LightningDamageDone + ChaosDamageDone;
	TotalDamageDone *= GlobalDamagePercent * (1 - GlobalDamageReductionPercent);
	TotalDamageDone *= DamageOverTimeDamage;
	if (TotalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, TotalDamageDone));
	}
}