// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// This header is for enums and structs used by classes and blueprints accross the game
// Collecting these in a single header helps avoid problems with recursive header includes
// It's also a good place to put things like data table row structs
// ----------------------------------------------------------------------------------------------------------------

#include "UObject/PrimaryAssetId.h"
#include "GE_Affix.h"
#include "RPGTypes.generated.h"

class URPGItem;

/** Struct representing a slot for an item, shown in the UI */
USTRUCT(BlueprintType)
struct ACTIONRPG_API FRPGItemSlot
{
	GENERATED_BODY()

	/** Constructor, -1 means an invalid slot */
	FRPGItemSlot()
		: SlotNumber(-1)
	{}

	FRPGItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;

	/** Equality operators */
	bool operator==(const FRPGItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FRPGItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FRPGItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};


/** Extra information about a URPGItem that is in a player's inventory */
USTRUCT(BlueprintType)
struct ACTIONRPG_API FRPGItemData
{
	GENERATED_BODY()

		/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FRPGItemData()
		: ItemCount(0)
		, ItemLevel(0)
	{
		PrefixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		SuffixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		ImplicitMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		EnchantMap = TMap<TSubclassOf<UGE_Affix>, int32>();
	}

	FRPGItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{
		PrefixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		SuffixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		ImplicitMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		EnchantMap = TMap<TSubclassOf<UGE_Affix>, int32>();
	}

	FRPGItemData(int32 InItemLevel)
		: ItemLevel(InItemLevel)
	{
		PrefixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		SuffixMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		ImplicitMap = TMap<TSubclassOf<UGE_Affix>, int32>();
		EnchantMap = TMap<TSubclassOf<UGE_Affix>, int32>();
	}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** The level of this item. This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affix")
	TMap<TSubclassOf<UGE_Affix>, int32> PrefixMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affix")
	TMap<TSubclassOf<UGE_Affix>, int32> SuffixMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affix")
	TMap<TSubclassOf<UGE_Affix>, int32> ImplicitMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affix")
	TMap<TSubclassOf<UGE_Affix>, int32> EnchantMap;

	bool AreMapsEqual(TMap<TSubclassOf<UGE_Affix>, int32> a, TMap<TSubclassOf<UGE_Affix>, int32> b) const
	{
		TArray<TSubclassOf<UGE_Affix>> OutKeysA, OutKeysB;
		a.GetKeys(OutKeysA);
		b.GetKeys(OutKeysB);
		if (OutKeysA != OutKeysB)
		{
			return false;
		}
		for (int i = 0; i < OutKeysA.Num() && i < OutKeysB.Num(); i++) 
		{
			if (a[OutKeysA[i]] != b[OutKeysB[i]])
			{
				return false;
			}
		}
		return true;
	}

	/** Equality operators */
	bool operator==(const FRPGItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel && AreMapsEqual(PrefixMap, Other.PrefixMap) && AreMapsEqual(SuffixMap, Other.SuffixMap) && AreMapsEqual(ImplicitMap, Other.ImplicitMap) && AreMapsEqual(EnchantMap, Other.EnchantMap);
	}
	bool operator!=(const FRPGItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount != -1;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FRPGItemData& Other)
	{
		ItemCount = FMath::Max(ItemCount + Other.ItemCount, 0);
		ItemLevel = FMath::Max3(Other.ItemLevel, 1, ItemLevel);
		PrefixMap = Other.PrefixMap;
		SuffixMap = Other.SuffixMap;
		ImplicitMap = Other.ImplicitMap;
		EnchantMap = Other.EnchantMap;
	}

	int32 UpdateItemCountLevel(int32 OtherItemCount, int32 OtherItemLevel = -1)
	{
		ItemCount = FMath::Max(ItemCount + OtherItemCount, 0);
		if (OtherItemLevel != -1)
		{
			ItemLevel = FMath::Max(FMath::Max(OtherItemLevel, 1), ItemLevel);
		}
		return ItemCount;
	}
};

/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, URPGLoot*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, URPGLoot*);

/** Delegate called when the contents of an inventory slot change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FRPGItemSlot, ItemSlot, URPGLoot*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FRPGItemSlot, URPGLoot*);

/** Delegate called when the entire inventory has been loaded, all items may have been replaced */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryLoaded);
DECLARE_MULTICAST_DELEGATE(FOnInventoryLoadedNative);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillTreeLoaded);
DECLARE_MULTICAST_DELEGATE(FOnSkillTreeLoadedNative);