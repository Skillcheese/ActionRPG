// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "GameplayEffect.h"
#include "GE_Affix.h"
#include "RPGArmorItem.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URPGArmorItem : public URPGItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Armor)
	TArray<FName> SectionsToHide;
};
