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
	//flat damage numbers
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChaosDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	RPGDamageStatics()
	{
		// Capture the Target's DefensePower attribute. Do not snapshot it, because we want to use the health value at the moment we apply the execution.
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, GlobalDamageReductionPercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningResistancePercent, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosResistancePercent, Target, false);

		//my definitions, snapshotted so it takes the value on launch, not on hit
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, GlobalDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, PhysicalDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, FireDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ColdDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, LightningDamagePercent, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ChaosDamagePercent, Source, true);

		//my definitions, snapshotted so it takes the value on launch, not on hit
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
	RelevantAttributesToCapture.Add(DamageStatics().GlobalDamageReductionPercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistancePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistancePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdResistancePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistancePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().ChaosResistancePercentDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().GlobalDamagePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamagePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireDamagePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdDamagePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningDamagePercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().ChaosDamagePercentDef);

	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ChaosDamageDef);

	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void URPGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// --------------------------------------
	//	Damage Done = Damage * AttackPower / DefensePower
	//	If DefensePower is 0, it is treated as 1.0
	// --------------------------------------

	float GlobalDamageReductionPercent = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().GlobalDamageReductionPercentDef, EvaluationParameters, GlobalDamageReductionPercent);

	float PhysicalResistancePercent = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalResistancePercentDef, EvaluationParameters, PhysicalResistancePercent);

	float FireResistancePercent= 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireResistancePercentDef, EvaluationParameters, FireResistancePercent);

	float ColdResistancePercent = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ColdResistancePercentDef, EvaluationParameters, ColdResistancePercent);

	float LightningResistancePercent = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightningResistancePercentDef, EvaluationParameters, LightningResistancePercent);

	float ChaosResistancePercent = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ChaosResistancePercentDef, EvaluationParameters, ChaosResistancePercent);

	float GlobalDamagePercent= 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().GlobalDamagePercentDef, EvaluationParameters, GlobalDamagePercent);

	float PhysicalDamagePercent= 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamagePercentDef, EvaluationParameters, PhysicalDamagePercent);

	float FireDamagePercent= 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireDamagePercentDef, EvaluationParameters, FireDamagePercent);

	float ColdDamagePercent = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ColdDamagePercentDef, EvaluationParameters, ColdDamagePercent);

	float LightningDamagePercent = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightningDamagePercentDef, EvaluationParameters, LightningDamagePercent);

	float ChaosDamagePercent = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ChaosDamagePercentDef, EvaluationParameters, ChaosDamagePercent);

	float PhysicalDamage= 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageDef, EvaluationParameters, PhysicalDamage);

	float FireDamage= 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireDamageDef, EvaluationParameters, FireDamage);

	float ColdDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ColdDamageDef, EvaluationParameters, ColdDamage);

	float LightningDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightningDamageDef, EvaluationParameters, LightningDamage);

	float ChaosDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ChaosDamageDef, EvaluationParameters, ChaosDamage);

	float PhysicalDamageDone = PhysicalDamage * PhysicalDamagePercent * (1 - PhysicalResistancePercent);
	float FireDamageDone = FireDamage * FireDamagePercent  * (1 - FireResistancePercent);
	float ColdDamageDone = ColdDamage * ColdDamagePercent * (1 - ColdResistancePercent);
	float LightningDamageDone = LightningDamage * LightningDamagePercent * (1 - LightningResistancePercent);
	float ChaosDamageDone = ChaosDamage * ChaosDamagePercent * (1 - ChaosResistancePercent);
	float TotalDamageDone = PhysicalDamageDone + FireDamageDone + ColdDamageDone + LightningDamageDone + ChaosDamageDone;
	TotalDamageDone *= GlobalDamagePercent * (1 - GlobalDamageReductionPercent);
	if (TotalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, TotalDamageDone));
	}
}