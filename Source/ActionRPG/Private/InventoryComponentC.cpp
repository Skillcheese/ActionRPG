// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "InventoryComponentC.h"

// Sets default values for this component's properties
UInventoryComponentC::UInventoryComponentC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InventoryItems = TMap<FIntPoint, URPGLoot*>();
	Equipement = TMap<FRPGItemSlot, URPGLoot*>();
}


bool UInventoryComponentC::LoadInventory()
{
	UWorld* World = GetWorld();
	URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;

	if (!GameInstance)
	{
		return false;
	}

	URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
	URPGAssetManager& AssetManager = URPGAssetManager::Get();
	if (CurrentSaveGame)
	{
		// Copy from save game into controller data
		bool bFoundAnySlots = false;
		for (const FSaveStruct& SaveStruct : CurrentSaveGame->InventoryData)
		{
			URPGLoot* LoadedItem = AssetManager.ForceLoadItem(SaveStruct.AssetId);
			if (LoadedItem != nullptr)
			{
				LoadedItem->Data = SaveStruct.Data;
				InventoryItems.Add(FIntPoint(SaveStruct.X, SaveStruct.Y), LoadedItem);
			}
		}

		for (const TPair<FRPGItemSlot, FSaveStruct>& SlotPair : CurrentSaveGame->SlottedItems)
		{
			if (SlotPair.Value.CheckIsValid())
			{
				URPGLoot* LoadedItem = AssetManager.ForceLoadItem(SlotPair.Value.AssetId);
				if (GameInstance->IsValidItemSlot(SlotPair.Key) && LoadedItem)
				{
					LoadedItem->Data = SlotPair.Value.Data;
					Equipement.Add(SlotPair.Key, LoadedItem);
					bFoundAnySlots = true;
				}
			}
		}
		return true;
	}

	return false;
}

// Called when the game starts
void UInventoryComponentC::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInventoryComponentC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

