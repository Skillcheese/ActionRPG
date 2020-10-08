// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGTypes.h"
#include "GE_Affix.h"
#include "RPGLoot.generated.h"

#define map TMap<TSubclassOf<UGE_Affix>,int32>

class RPGItem;
/**
 * 
 */
UCLASS(BlueprintType)
class ACTIONRPG_API URPGLoot : public UObject
{
	
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	URPGItem* BaseType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FRPGItemData Data;

	UFUNCTION(BlueprintCallable, Category = Affix)
	TMap<TSubclassOf<UGE_Affix>, int32> GetItemAffixes(TMap<TSubclassOf<UGE_Affix>, int32> &PrefixMap, TMap<TSubclassOf<UGE_Affix>, int32> &SuffixMap, TMap<TSubclassOf<UGE_Affix>, int32> &ImplicitMap, TMap<TSubclassOf<UGE_Affix>, int32> &EnchantMap);

	UFUNCTION(BlueprintPure, Category = Item)
	int32 GetItemCount();

	UFUNCTION(BlueprintPure, Category = Item)
	int32 GetItemLevel();

	UFUNCTION(BlueprintPure, Category = Item)
	void GetItemDimensions(int32 &Width, int32 &Height);

	///0 for unarmed, 1 for one handed, 2 for 2 handed
	UFUNCTION(BlueprintPure, Category = Item)
	int32 GetItemHandedness();

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 SetItemCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 UpdateItemCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 SetItemLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 UpdateItemLevel(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = Item)
	bool isWeapon();
};
