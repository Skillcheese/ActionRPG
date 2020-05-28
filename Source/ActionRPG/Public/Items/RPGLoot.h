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

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 SetItemCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = Item)
	int32 UpdateItemCount(int32 Count);
};
