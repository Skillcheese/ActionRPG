// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGItem.h"
#include "RPGLoot.h"

map URPGLoot::GetItemAffixes(map &PrefixMap, map &SuffixMap, map &ImplicitMap, map &EnchantMap)
{
	map r = map();
	PrefixMap = Data.PrefixMap;
	SuffixMap = Data.SuffixMap;
	ImplicitMap = Data.ImplicitMap;
	EnchantMap = Data.EnchantMap;
	r.Append(PrefixMap);
	r.Append(SuffixMap);
	r.Append(ImplicitMap);
	r.Append(EnchantMap);
	return r;
}

int32 URPGLoot::GetItemCount()
{
	return Data.ItemCount;
}

int32 URPGLoot::GetItemLevel()
{
	return Data.ItemLevel;
}

void URPGLoot::GetItemDimensions(int32 & Width, int32 & Height)
{
	Width = 1;
	Height = 1;
#define Check(Name, w, h) \
	if (BaseType->ItemType == FPrimaryAssetType(FName(Name))) \
	{ \
		Width = w; \
		Height = h; \
	}

	Check("Sword1H", 1, 3);
	Check("Sword2H", 2, 3);
	Check("Axe1H", 1, 3);
	Check("Axe2H", 2, 3);
	Check("Hammer1H", 1, 3);
	Check("Hammer2H", 2, 3);
	Check("Bow", 2, 3);
	Check("Scythe", 2, 3);
	Check("Staff", 2, 3);
	Check("Wand", 1, 3);
	Check("Dagger", 1, 3);
	Check("OffHand", 1, 3);
	Check("Shield", 1, 3);

	Check("Gloves", 2, 2);
	Check("Boots", 2, 2);
	Check("Helmet", 2, 2);
	Check("Chest", 2, 3);
	Check("Jewelry", 1, 1);
}

int32 URPGLoot::GetItemHandedness()
{
#define CheckHand(Name, num) \
	if (BaseType->ItemType == FPrimaryAssetType(FName(Name))) \
	{ \
		return num; \
	}
	CheckHand("Sword1H", 1);
	CheckHand("Sword2H", 2);
	CheckHand("Axe1H", 1);
	CheckHand("Axe2H", 2);
	CheckHand("Hammer1H", 1);
	CheckHand("Hammer2H", 2);
	CheckHand("Bow", 2);
	CheckHand("Scythe", 2);
	CheckHand("Staff", 2);
	CheckHand("Wand", 1);
	CheckHand("Dagger", 1);
	CheckHand("OffHand", 1);
	CheckHand("Shield", 1);
	return -1;
}

int32 URPGLoot::SetItemCount(int32 Count)
{
	return UpdateItemCount(Count - Data.ItemCount);
}

int32 URPGLoot::UpdateItemCount(int32 Count)
{
	return Data.UpdateItemCountLevel(Count);
}

int32 URPGLoot::SetItemLevel(int32 NewLevel)
{
	return Data.ItemLevel = NewLevel;
}

int32 URPGLoot::UpdateItemLevel(int32 Amount)
{
	return SetItemLevel(Data.ItemLevel + Amount);
}
