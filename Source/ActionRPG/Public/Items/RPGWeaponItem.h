// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Items/RPGItem.h"
#include "RPGWeaponItem.generated.h"

/** Native base class for weapons, should be blueprinted */
UCLASS()
class ACTIONRPG_API URPGWeaponItem : public URPGItem
{
	GENERATED_BODY()

public:
	/** Constructor */
	URPGWeaponItem()
	{
		ItemType = URPGAssetManager::WeaponItemType;
	}

	//0 for unarmed, 1 for one-handed, 2 for two-handed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	int32 WeaponWieldType;
};