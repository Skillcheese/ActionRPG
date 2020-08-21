// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGAssetManager.h"
#include "Items/RPGItem.h"
#include "AbilitySystemGlobals.h"

#define CREATE(_type_, _text_) \
	const FPrimaryAssetType	URPGAssetManager::_type_ = TEXT(_text_)

CREATE(PotionItemType, "Potion");
CREATE(SkillItemType, "Skill");
CREATE(TokenItemType, "Token");
CREATE(WeaponItemType, "Weapon");
CREATE(Sword1HItemType, "Sword1H");
CREATE(Sword2HItemType, "Sword2H");
CREATE(Axe1HItemType, "Axe1H");
CREATE(Axe2HItemType, "Axe2H");
CREATE(Hammer1HItemType, "Hammer1H");
CREATE(Hammer2HItemType, "Hammer2H");
CREATE(BowItemType, "Bow");
CREATE(ScytheItemType, "Scythe");
CREATE(StaffItemType, "Staff");
CREATE(WandItemType, "Wand");
CREATE(DaggerItemType, "Dagger");
CREATE(OffHandItemType, "OffHand");
CREATE(ShieldItemType, "Shield");
CREATE(GlovesItemType, "Gloves");
CREATE(BootsItemType, "Boots");
CREATE(HelmetItemType, "Helmet");
CREATE(ChestItemType, "Chest");
CREATE(JewelryItemType, "Jewelry");
CREATE(SkillNodeBase, "SkillNodeBase");

URPGAssetManager& URPGAssetManager::Get()
{
	URPGAssetManager* This = Cast<URPGAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogActionRPG, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
		return *NewObject<URPGAssetManager>(); // never calls this
	}
}

void URPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}


URPGLoot* URPGAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{	
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	URPGItem* LoadedItem = Cast<URPGItem>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogActionRPG, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}
	if (LoadedItem == nullptr)
	{
		return nullptr;
	}
	URPGLoot* Loot = NewObject<URPGLoot>(this);
	if (Loot)
	{
		Loot->BaseType = LoadedItem;
	}
	return Loot;
}

USkillNodeBase * URPGAssetManager::ForceLoadSkillNode(const FPrimaryAssetId & PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UObject* object = ItemPath.TryLoad();
	USkillNodeBase* LoadedNode = Cast<USkillNodeBase>(ItemPath.TryLoad());
	if (bLogWarning && LoadedNode == nullptr)
	{
		UE_LOG(LogActionRPG, Warning, TEXT("Failed to load skill node for identifier %s!"), *PrimaryAssetId.ToString());
	}
	if (LoadedNode == nullptr)
	{
		return nullptr;
	}
	return LoadedNode;
}
