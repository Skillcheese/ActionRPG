// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGPlayerControllerBase.h"
#include "RPGCharacterBase.h"
#include "RPGGameInstanceBase.h"
#include "RPGSaveGame.h"
#include "Items/RPGItem.h"

bool ARPGPlayerControllerBase::AddInventoryItem(URPGLoot* NewItem, int32 count, bool bAutoSlot)
{
	bool bChanged = false;
	if (!NewItem)
	{
		UE_LOG(LogActionRPG, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
		return false;
	}

	if (NewItem->GetItemCount() < 0 || NewItem->Data.ItemLevel < 0)
	{
		UE_LOG(LogActionRPG, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count or level!"), *NewItem->GetName());
		return false;
	}
	// Find current item data, which may be empty
	if (InventoryItems.Contains(NewItem))
	{
		NewItem->Data.UpdateItemCountLevel(count);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}
	else
	{
		URPGLoot** OldItemPointer = InventoryItems.FindByPredicate([&](URPGLoot* Item) 
		{
			if (!Item || !NewItem)
			{
				return false;
			}
			return Item->BaseType->GetPrimaryAssetId() == NewItem->BaseType->GetPrimaryAssetId();
		});

		URPGLoot* OldItem = nullptr;

		if (OldItemPointer)
		{
			OldItem = *OldItemPointer;
		}
		bool a = NewItem->BaseType->Stackable && NewItem->GetItemCount() <= 0;
		bool b = NewItem->BaseType->ItemName.EqualTo(FText::FromString(TEXT("Souls")));
		if (OldItem)
		{
			if (OldItem->BaseType->Stackable)
			{
				OldItem->Data.UpdateItemCountLevel(count);
				bChanged = true;
			}
			else
			{
				if (!a || b) {
					InventoryItems.Add(NewItem);
					NotifyInventoryItemChanged(true, NewItem);
					bChanged = true;
				}
			}
		}
		else
		{
			if (!a || b)
			{
				NewItem->Data.ItemCount = count;
				InventoryItems.Add(NewItem);
				NotifyInventoryItemChanged(true, NewItem);
				bChanged = true;
			}
		}
	}
	if (bAutoSlot)
	{
		// Slot item if required
		bChanged |= FillEmptySlotWithItem(NewItem);
	}
	if (bChanged)
	{
		// If anything changed, write to save game
		SaveInventory();
		return true;
	}
	return false;
}

bool ARPGPlayerControllerBase::RemoveInventoryItem(URPGLoot* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogActionRPG, Warning, TEXT("RemoveInventoryItem: Failed trying to remove null item!"));
		return false;
	}
	if (RemovedItem)
	{
		if (InventoryItems.Contains(RemovedItem))
		{
			if (RemovedItem->BaseType->Stackable)
			{
				bool isSlotted = false;
				for (TPair<FRPGItemSlot, URPGLoot*>& Pair : SlottedItems)
				{
					if (Pair.Value == RemovedItem)
					{
						isSlotted = true;
						break;
					}
				}
				if (isSlotted)
				{
					InventoryItems.Remove(RemovedItem);
				}
				else
				{
					if (RemovedItem->Data.UpdateItemCountLevel(-RemoveCount) <= 0)
					{
						InventoryItems.Remove(RemovedItem);
					}
				}
				
			}
			else
			{
				InventoryItems.Remove(RemovedItem);
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	for (TPair<FRPGItemSlot, URPGLoot*>& Pair : SlottedItems)
	{
		if (Pair.Value == RemovedItem)
		{
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}
	// If we got this far, there is a change so notify and save
	NotifyInventoryItemChanged(false, RemovedItem);

	SaveInventory();
	return true;
}

int32 ARPGPlayerControllerBase::SetSkillNodeTaken(USkillNodeBase * SkillNode, bool Taken)
{
	if (!SkillNode)
	{
		return -1; //Failed
	}
	for (int i = 0; i < SkillNodesTaken.Num(); i++)
	{
		USkillNodeBase* CurrentNode = SkillNodesTaken[i];
		if (CurrentNode)
		{
			if (CurrentNode->GetPrimaryAssetId() == SkillNode->GetPrimaryAssetId())
			{
				if (Taken)
				{
					return 0; //Was already in the list
				}
				else
				{
					SkillNodesTaken.RemoveAt(i);
					RefreshEffects();
					SaveInventory();
					return 1;
				}
			}
		}
	}
	if (Taken)
	{
		SkillNodesTaken.Add(SkillNode);
		RefreshEffects();
		SaveInventory();
		return 1;
	}
	return -2;
}

void ARPGPlayerControllerBase::GetInventoryItems(TArray<URPGLoot*>& Items, FPrimaryAssetType ItemType)
{
	for (URPGLoot*& Item : InventoryItems)
	{
		if (Item)
		{
			FPrimaryAssetId AssetId = Item->BaseType->GetPrimaryAssetId();

			// Filters based on item type
			if (AssetId.PrimaryAssetType == ItemType || !ItemType.IsValid())
			{
				Items.Add(Item);
			}
		}	
	}
}

TArray<USkillNodeBase*> ARPGPlayerControllerBase::GetSkillNodesTaken()
{
	return SkillNodesTaken;
}

bool ARPGPlayerControllerBase::SetSlottedItem(FRPGItemSlot ItemSlot, URPGLoot* Item)
{
	// Iterate entire inventory because we need to remove from old slot
	bool bFound = false;
	for (TPair<FRPGItemSlot, URPGLoot*>& Pair : SlottedItems)
	{
		if (Pair.Key == ItemSlot)
		{
			// Add to new slot
			bFound = true;
			Pair.Value = Item;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
		else if (Item != nullptr && Pair.Value == Item)
		{
			// If this item was found in another slot, remove it
			Pair.Value = nullptr;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}

	if (bFound)
	{
		SaveInventory();
		return true;
	}

	return false;
}

TMap<TSubclassOf<UGE_Affix>, int32> ARPGPlayerControllerBase::GetInventoryItemAffixes(URPGLoot *Item, TMap<TSubclassOf<UGE_Affix>, int32> &PrefixMap, TMap<TSubclassOf<UGE_Affix>, int32> &SuffixMap, TMap<TSubclassOf<UGE_Affix>, int32> &ImplicitMap, TMap<TSubclassOf<UGE_Affix>, int32> &EnchantMap)
{
	TMap<TSubclassOf<UGE_Affix>, int32> r = TMap<TSubclassOf<UGE_Affix>, int32>();
	if (Item)
	{
		PrefixMap = Item->Data.PrefixMap;
		SuffixMap = Item->Data.SuffixMap;
		ImplicitMap = Item->Data.ImplicitMap;
		EnchantMap = Item->Data.EnchantMap;
		r.Append(PrefixMap);
		r.Append(SuffixMap);
		r.Append(ImplicitMap);
		r.Append(EnchantMap);
	}
	return r;
}

bool ARPGPlayerControllerBase::UpdateItemAffixes(URPGLoot* Item, TMap<TSubclassOf<UGE_Affix>, int32> PrefixMap, TMap<TSubclassOf<UGE_Affix>, int32> SuffixMap, TMap<TSubclassOf<UGE_Affix>, int32> ImplicitMap, TMap<TSubclassOf<UGE_Affix>, int32> EnchantMap)
{
	bool bChanged = false;

	Item->Data.PrefixMap = PrefixMap;
	Item->Data.SuffixMap = SuffixMap;
	Item->Data.ImplicitMap = ImplicitMap;
	Item->Data.EnchantMap = EnchantMap;
	NotifyInventoryItemChanged(true, Item);
	bChanged = true;
	if (bChanged)
	{
		// If anything changed, write to save game
		SaveInventory();
		return true;
	}
	return false;
}

URPGLoot* ARPGPlayerControllerBase::GetSlottedItem(FRPGItemSlot ItemSlot)
{
	URPGLoot* const* FoundItem = SlottedItems.Find(ItemSlot);

	if (FoundItem)
	{
		return *FoundItem;
	}
	return nullptr;
}

URPGLoot * ARPGPlayerControllerBase::GetSouls(int32 &Count)
{
	URPGLoot* Item = GetSoulsItem();
	if (Item)
	{
		Count = Item->GetItemCount();
		return Item;
	}
	return nullptr;
}

URPGLoot * ARPGPlayerControllerBase::GetSoulsItem()
{
	URPGLoot** SoulsPointer = InventoryItems.FindByPredicate([](URPGLoot* Item)
	{
		if (!Item)
		{
			return false;
		}
		return Item->BaseType->ItemName.EqualTo(FText::FromString(TEXT("Souls")));
	});
	if (SoulsPointer)
	{
		URPGLoot* Souls = *SoulsPointer;
		if (Souls)
		{
			return Souls;
		}
	}
	return nullptr;
}

bool ARPGPlayerControllerBase::AddSouls(int32 amount, int32 &Count)
{
	URPGLoot* Item = GetSoulsItem();
	if (Item)
	{
		Count = Item->Data.UpdateItemCountLevel(amount);
		return true;
	}
	return false;
}

bool ARPGPlayerControllerBase::SoulsPurchase(int32 amount, int32 & Count)
{
	int32 CurrentSouls = 0;
	GetSouls(CurrentSouls);
	if (CurrentSouls >= amount)
	{
		AddSouls(-amount, Count);
		return true;
	}
	return false;
}

void ARPGPlayerControllerBase::FillEmptySlots()
{
	bool bShouldSave = false;
	for (URPGLoot*& Item: InventoryItems)
	{
		bShouldSave |= FillEmptySlotWithItem(Item);
	}

	if (bShouldSave)
	{
		SaveInventory();
	}
}

bool ARPGPlayerControllerBase::SaveInventory()
{
	UWorld* World = GetWorld();
	URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;

	if (!GameInstance)
	{
		return false;
	}

	URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
	if (CurrentSaveGame)
	{
		// Reset cached data in save game before writing to it
		CurrentSaveGame->InventoryData.Reset();
		CurrentSaveGame->SlottedItems.Reset();
		CurrentSaveGame->SkillData.Reset();

		for (URPGLoot*& Item : InventoryItems)
		{
			if (Item)
			{
				CurrentSaveGame->InventoryData.Add(FSaveStruct(Item->BaseType->GetPrimaryAssetId(), Item->Data));
			}
		}

		for (const TPair<FRPGItemSlot, URPGLoot*>& SlotPair : SlottedItems)
		{
			if (SlotPair.Value)
			{
				CurrentSaveGame->SlottedItems.Add(SlotPair.Key, FSaveStruct(SlotPair.Value->BaseType->GetPrimaryAssetId(), SlotPair.Value->Data));
			}
		}
		for (USkillNodeBase*&SkillNode : SkillNodesTaken)
		{
			if (SkillNode)
			{
				CurrentSaveGame->SkillData.Add(SkillNode->GetPrimaryAssetId());
			}
		}

		// Now that cache is updated, write to disk
		GameInstance->WriteSaveGame();
		return true;
	}
	return false;
}

bool ARPGPlayerControllerBase::RefreshEffects()
{
	APawn* pawn = GetPawn();
	if (pawn)
	{
		ARPGCharacterBase* character = Cast<ARPGCharacterBase>(pawn);
		if (character)
		{
			character->SkillTreeNodes = SkillNodesTaken;
			return character->RefreshEffects();
		}
	}
	return false;
}

bool ARPGPlayerControllerBase::LoadInventory()
{
	InventoryItems.Reset();
	SlottedItems.Reset();

	// Fill in slots from game instance
	UWorld* World = GetWorld();
	URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;

	if (!GameInstance)
	{
		return false;
	}

	for (const TPair<FPrimaryAssetType, int32>& Pair : GameInstance->ItemSlotsPerType)
	{
		for (int32 SlotNumber = 0; SlotNumber < Pair.Value; SlotNumber++)
		{
			SlottedItems.Add(FRPGItemSlot(Pair.Key, SlotNumber), nullptr);
		}
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
				InventoryItems.Add(LoadedItem);
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
					SlottedItems.Add(SlotPair.Key, LoadedItem);
					bFoundAnySlots = true;
				}
			}
		}

		if (!bFoundAnySlots)
		{
			// Auto slot items as no slots were saved
			FillEmptySlots();
		}

		NotifyInventoryLoaded();

		return true;
	}

	// Load failed but we reset inventory, so need to notify UI
	NotifyInventoryLoaded();

	return false;
}

bool ARPGPlayerControllerBase::LoadSkillTree()
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
		bool LoadSuccessful = true;
		for (const FPrimaryAssetId& SaveData : CurrentSaveGame->SkillData)
		{
			USkillNodeBase* LoadedNode = AssetManager.ForceLoadSkillNode(SaveData);
			if (LoadedNode != nullptr)
			{
				bool go = true;
				for (int i = 0; i < SkillNodesTaken.Num(); i++)
				{
					if (SkillNodesTaken[i]->GetPrimaryAssetId() == LoadedNode->GetPrimaryAssetId())
					{
						go = false;
						break;
					}
				}
				if (go)
				{
					SkillNodesTaken.Add(LoadedNode);
				}
			}
			else
			{
				LoadSuccessful = false;
			}
		}
		if (LoadSuccessful)
		{
			NotifySkillTreeLoaded();
			return true;
		}
	}
	return false;
}

bool ARPGPlayerControllerBase::FillEmptySlotWithItem(URPGLoot* NewItem)
{
	// Look for an empty item slot to fill with this item
	FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;
	FRPGItemSlot EmptySlot;
	for (TPair<FRPGItemSlot, URPGLoot*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == NewItemType)
		{
			if (Pair.Value == NewItem)
			{
				// Item is already slotted
				return false;
			}
			else if (Pair.Value == nullptr && (!EmptySlot.IsValid() || EmptySlot.SlotNumber > Pair.Key.SlotNumber))
			{
				// We found an empty slot worth filling
				if (NewItem->GetItemCount() > 0)
				{
					EmptySlot = Pair.Key;
				}
				else
				{
					EmptySlot = Pair.Key;
				}
			}
		}
	}

	if (EmptySlot.IsValid())
	{
		SlottedItems[EmptySlot] = NewItem;
		NotifySlottedItemChanged(EmptySlot, NewItem);
		return true;
	}

	return false;
}

void ARPGPlayerControllerBase::NotifyInventoryItemChanged(bool bAdded, URPGLoot* Item)
{
	// Notify native before blueprint
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
	OnInventoryItemChanged.Broadcast(bAdded, Item);

	// Call BP update event
	InventoryItemChanged(bAdded, Item);
}

void ARPGPlayerControllerBase::NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGLoot* Item)
{
	// Notify native before blueprint
	OnSlottedItemChangedNative.Broadcast(ItemSlot, Item);
	OnSlottedItemChanged.Broadcast(ItemSlot, Item);

	// Call BP update event
	SlottedItemChanged(ItemSlot, Item);
}

void ARPGPlayerControllerBase::NotifyInventoryLoaded()
{
	// Notify native before blueprint
	OnInventoryLoadedNative.Broadcast();
	OnInventoryLoaded.Broadcast();
}

void ARPGPlayerControllerBase::NotifySkillTreeLoaded()
{
	OnSkillTreeLoadedNative.Broadcast();
	OnSkillTreeLoaded.Broadcast();
}

void ARPGPlayerControllerBase::BeginPlay()
{
	// Load inventory off save game before starting play
	LoadInventory();
	LoadSkillTree();

	Super::BeginPlay();
}

void ARPGPlayerControllerBase::Possess(APawn* NewPawn)
{
	Super::Possess(NewPawn);

	// Notify blueprint about the possession, only if it is valid
	// In a network game this would need to be replicated
	if (NewPawn)
	{
		ReceivePossess(NewPawn);
	}
}

void ARPGPlayerControllerBase::UnPossess()
{
	APawn* PreviousPawn = GetPawn();

	if (PreviousPawn)
	{
		// Only call if we had one before		
		ReceiveUnPossess(PreviousPawn);
	}
	
	Super::UnPossess();
}