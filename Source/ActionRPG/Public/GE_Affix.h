// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_Affix.generated.h"

UENUM()
enum AffixType
{
	Prefix,
	Suffix,
	Implicit,
	Enchant
};

/**
 * 
 */
UCLASS()
class ACTIONRPG_API UGE_Affix : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Affix)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Affix)
	FString DescriptionB;
};

