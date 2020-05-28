// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "SkillNode.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class ACTIONRPG_API USkillNode : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	USkillNode()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillTree)
	TMap<TSubclassOf<UGE_Affix>, int32> NodeAffixes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillTree)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillTree)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillTree)
	FSlateBrush SkillIcon;

	UFUNCTION(BlueprintCallable, Category = SkillTree)
	FString GetIdentifierString() const;
};

USTRUCT(BlueprintType)
struct ACTIONRPG_API FSkillSaveStruct
{
	GENERATED_BODY()
public:
	FSkillSaveStruct()
	{
	}

	FSkillSaveStruct(FPrimaryAssetId Id, bool _Taken)
	{
		AssetId = Id;
		Taken = _Taken;
	}
	bool operator==(const FSkillSaveStruct &other) const
	{
		return AssetId == other.AssetId;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillTree)
	FPrimaryAssetId AssetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillTree)
	bool Taken;
};