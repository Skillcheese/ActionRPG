// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SkillNode.h"

FString USkillNode::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}
