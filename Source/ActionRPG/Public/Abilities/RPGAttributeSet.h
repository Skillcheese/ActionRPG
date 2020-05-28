// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/** This holds all of the attributes used by abilities, it instantiates a copy of this on every character */
UCLASS()
class ACTIONRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	URPGAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

	/** MaxHealth is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)

	/** Current Mana, used to execute special abilities. Capped by MaxMana */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Mana)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ManaRegen)

	/** MoveSpeed affects how fast characters can move */
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MoveSpeed)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)


	//MY PROPERTIES
	/**********************************************************************************************************
	Defensive properties
	**********************************************************************************************************/
	UPROPERTY(BlueprintReadOnly, Category = "Global Damage", ReplicatedUsing = OnRep_GlobalDamageReductionPercent)
	FGameplayAttributeData GlobalDamageReductionPercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, GlobalDamageReductionPercent)

	UPROPERTY(BlueprintReadOnly, Category = "Physical Damage", ReplicatedUsing = OnRep_PhysicalResistancePercent)
	FGameplayAttributeData PhysicalResistancePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalResistancePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Fire Damage", ReplicatedUsing = OnRep_FireResistancePercent)
	FGameplayAttributeData FireResistancePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireResistancePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Cold Damage", ReplicatedUsing = OnRep_ColdResistancePercent)
	FGameplayAttributeData ColdResistancePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ColdResistancePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Lightning Damage", ReplicatedUsing = OnRep_LightningResistancePercent)
	FGameplayAttributeData LightningResistancePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningResistancePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Chaos Damage", ReplicatedUsing = OnRep_ChaosResistancePercent)
	FGameplayAttributeData ChaosResistancePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ChaosResistancePercent)

	/**********************************************************************************************************
	Offensive properties
	**********************************************************************************************************/

	UPROPERTY(BlueprintReadOnly, Category = "Global Damage", ReplicatedUsing = OnRep_GlobalDamagePercent)
	FGameplayAttributeData GlobalDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, GlobalDamagePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Physical Damage", ReplicatedUsing = OnRep_PhysicalDamagePercent)
	FGameplayAttributeData PhysicalDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalDamagePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Fire Damage", ReplicatedUsing = OnRep_FireDamagePercent)
	FGameplayAttributeData FireDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireDamagePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Cold Damage", ReplicatedUsing = OnRep_ColdDamagePercent)
	FGameplayAttributeData ColdDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ColdDamagePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Lightning Damage", ReplicatedUsing = OnRep_LightningDamagePercent)
	FGameplayAttributeData LightningDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningDamagePercent)

	UPROPERTY(BlueprintReadOnly, Category = "Chaos Damage", ReplicatedUsing = OnRep_ChaosDamagePercent)
	FGameplayAttributeData ChaosDamagePercent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ChaosDamagePercent)

	/**********************************************************************************************************
	Result properties, don't modify these directly
	**********************************************************************************************************/

	UPROPERTY(BlueprintReadOnly, Category = "Physical Damage", ReplicatedUsing = OnRep_PhysicalDamage)
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Fire Damage", ReplicatedUsing = OnRep_FireDamage)
	FGameplayAttributeData FireDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Cold Damage", ReplicatedUsing = OnRep_ColdDamage)
	FGameplayAttributeData ColdDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ColdDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Lightning Damage", ReplicatedUsing = OnRep_LightningDamage)
	FGameplayAttributeData LightningDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Chaos Damage", ReplicatedUsing = OnRep_ChaosDamage)
	FGameplayAttributeData ChaosDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ChaosDamage)


protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
	virtual void OnRep_Health();

	UFUNCTION()
	virtual void OnRep_MaxHealth();

	UFUNCTION()
	virtual void OnRep_Mana();

	UFUNCTION()
	virtual void OnRep_MaxMana();

	UFUNCTION()
	virtual void OnRep_ManaRegen();

	UFUNCTION()
	virtual void OnRep_MoveSpeed();

	UFUNCTION()
	virtual void OnRep_GlobalDamageReductionPercent();

	UFUNCTION()
	virtual void OnRep_PhysicalResistancePercent();

	UFUNCTION()
	virtual void OnRep_FireResistancePercent();

	UFUNCTION()
	virtual void OnRep_ColdResistancePercent();

	UFUNCTION()
	virtual void OnRep_LightningResistancePercent();

	UFUNCTION()
	virtual void OnRep_ChaosResistancePercent();

	UFUNCTION()
	virtual void OnRep_GlobalDamagePercent();

	UFUNCTION()
	virtual void OnRep_PhysicalDamagePercent();

	UFUNCTION()
	virtual void OnRep_FireDamagePercent();

	UFUNCTION()
	virtual void OnRep_ColdDamagePercent();

	UFUNCTION()
	virtual void OnRep_LightningDamagePercent();

	UFUNCTION()
	virtual void OnRep_ChaosDamagePercent();

	UFUNCTION()
	virtual void OnRep_PhysicalDamage();

	UFUNCTION()
	virtual void OnRep_FireDamage();

	UFUNCTION()
	virtual void OnRep_ColdDamage();

	UFUNCTION()
	virtual void OnRep_LightningDamage();

	UFUNCTION()
	virtual void OnRep_ChaosDamage();
};