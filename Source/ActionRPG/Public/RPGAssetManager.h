// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "Engine/AssetManager.h"
#include "Items/RPGLoot.h"
#include "SkillNodeBase.h"
#include "RPGAssetManager.generated.h"


/**
 * Game implementation of asset manager, overrides functionality and stores game-specific types
 * It is expected that most games will want to override AssetManager as it provides a good place for game-specific loading logic
 * This is used by setting AssetManagerClassName in DefaultEngine.ini
 */
UCLASS()
class ACTIONRPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	URPGAssetManager() {}
	virtual void StartInitialLoading() override;

	/** Static types for items */
	static const FPrimaryAssetType	PotionItemType;
	static const FPrimaryAssetType	SkillItemType;
	static const FPrimaryAssetType	TokenItemType;
	static const FPrimaryAssetType	WeaponItemType;
	static const FPrimaryAssetType	Sword1HItemType;
	static const FPrimaryAssetType	Sword2HItemType;
	static const FPrimaryAssetType	Axe1HItemType;
	static const FPrimaryAssetType	Axe2HItemType;
	static const FPrimaryAssetType	Hammer1HItemType;
	static const FPrimaryAssetType	Hammer2HItemType;
	static const FPrimaryAssetType	BowItemType;
	static const FPrimaryAssetType	ScytheItemType;
	static const FPrimaryAssetType	StaffItemType;
	static const FPrimaryAssetType	WandItemType;
	static const FPrimaryAssetType	DaggerItemType;
	static const FPrimaryAssetType	OffHandItemType;
	static const FPrimaryAssetType	ShieldItemType;
	static const FPrimaryAssetType	GlovesItemType;
	static const FPrimaryAssetType	BootsItemType;
	static const FPrimaryAssetType	HelmetItemType;
	static const FPrimaryAssetType	ChestItemType;
	static const FPrimaryAssetType	JewelryItemType;
	static const FPrimaryAssetType	SkillNodeBase;

	/** Returns the current AssetManager object */
	static URPGAssetManager& Get();

	/**
	 * Synchronously loads an RPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	URPGLoot* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
	USkillNodeBase* ForceLoadSkillNode(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};

