// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

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
