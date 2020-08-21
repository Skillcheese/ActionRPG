// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGSaveGame.h"
#include "RPGGameInstanceBase.h"

void URPGSaveGame::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading() && SavedDataVersion != ERPGSaveGameVersion::LatestVersion)
	{
		if (SavedDataVersion < ERPGSaveGameVersion::AddedItemData)
		{
			
		}
		
		SavedDataVersion = ERPGSaveGameVersion::LatestVersion;
	}
}