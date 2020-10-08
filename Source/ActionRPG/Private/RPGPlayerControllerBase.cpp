// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGPlayerControllerBase.h"
#include "RPGCharacterBase.h"
#include "RPGGameInstanceBase.h"
#include "RPGSaveGame.h"
#include "Items/RPGItem.h"

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

TArray<USkillNodeBase*> ARPGPlayerControllerBase::GetSkillNodesTaken()
{
	return SkillNodesTaken;
}

bool ARPGPlayerControllerBase::SetSlottedItem(FRPGItemSlot ItemSlot, URPGLoot* Item)
{
	// Iterate entire inventory because we need to remove from old slot
	bool bFound = false;
#define AddEquipment() \
GetInventoryComponent()->Equipement.Add(ItemSlot, Item); \
NotifySlottedItemChanged(ItemSlot, Item); \
SaveInventory(); \

/*
const FIntPoint *key = GetInventoryComponent()->InventoryItems.FindKey(Item); \
if (key) \
{ \
GetInventoryComponent()->InventoryItems.Remove(*key); \
} \
*/
	if (Item->isWeapon())
	{
		FRPGItemSlot Slot0Key = FRPGItemSlot(FPrimaryAssetType(FName("Weapon")), 0);
		FRPGItemSlot Slot1Key = FRPGItemSlot(FPrimaryAssetType(FName("Weapon")), 1);
		URPGLoot** Slot0Ptr = GetInventoryComponent()->Equipement.Find(Slot0Key);
		URPGLoot** Slot1Ptr = GetInventoryComponent()->Equipement.Find(Slot1Key);
		URPGLoot* Slot0 = nullptr;
		URPGLoot* Slot1 = nullptr;
		if (Slot0Ptr)
		{
			Slot0 = *Slot0Ptr;
		}
		if (Slot1Ptr)
		{
			Slot1 = *Slot1Ptr;
		}
#define DoSlot(num) \
if (Slot##num)  \
{ \
	GetInventoryComponent()->AddNewItemToInventory(Slot##num, Item);\
	GetInventoryComponent()->Equipement.Remove(Slot##num##Key); \
}\

		//NotifySlottedItemChanged(Slot##num##Key, nullptr);
		if (Item->GetItemHandedness() == 2)
		{
			DoSlot(0);
			DoSlot(1);
			ItemSlot.SlotNumber = 0;
			AddEquipment();
			return true;
		}
		else if (Item->GetItemHandedness() == 1)
		{
			if (ItemSlot.SlotNumber == 0)
			{
				if (Slot1)
				{
					if (Slot1->GetItemHandedness() == 2)
					{
						DoSlot(1);
					}
				}
				DoSlot(0);
				AddEquipment();
				return true;
			}
			if (ItemSlot.SlotNumber == 1)
			{
				if (Slot0)
				{
					if (Slot0->GetItemHandedness() == 2)
					{
						DoSlot(0);
					}
				}
				DoSlot(1);
				AddEquipment();
				return true;
			}
		}
	}
	else
	{
		for (TPair<FRPGItemSlot, URPGLoot*>& Pair : GetInventoryComponent()->Equipement)
		{
			if (Pair.Key == ItemSlot)
			{
				bFound = true;
				URPGLoot* Temp = nullptr;
				if (Pair.Value)
				{//need to swap
					Temp = Pair.Value;
				}
				// Add to new slot
				if (Temp)
				{
					GetInventoryComponent()->AddNewItemToInventory(Temp, Item);
					NotifyInventoryItemChanged(true, Temp);
				}
				AddEquipment();
				return true;
			}
			else if (Item && Pair.Value == Item)
			{
				// If this item was found in another slot, remove it
				Pair.Value = nullptr;
				NotifySlottedItemChanged(Pair.Key, Pair.Value);
			}
		}
	}
	AddEquipment();
	return true;
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
	UInventoryComponentC* InventoryComponent = GetInventoryComponent();
	if (InventoryComponent)
	{
		URPGLoot* const* FoundItem = InventoryComponent->Equipement.Find(ItemSlot);
		if (FoundItem)
		{
			return *FoundItem;
		}
	}
	return nullptr;
}

int32 ARPGPlayerControllerBase::GetSouls()
{
	return Souls;
}

bool ARPGPlayerControllerBase::AddSouls(int32 amount, int32 &Count)
{
	Souls += amount;
	return true;
}

bool ARPGPlayerControllerBase::SoulsPurchase(int32 amount, int32 & Count)
{
	if (Souls >= amount)
	{
		AddSouls(-amount, Count);
		return true;
	}
	return false;
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
		UInventoryComponentC* InventoryComponent = GetInventoryComponent();
		if (InventoryComponent)
		{
			for (TPair<FIntPoint, URPGLoot*> Item : InventoryComponent->InventoryItems)
			{
				if (Item.Value)
				{
					CurrentSaveGame->InventoryData.Add(FSaveStruct(Item.Key.X,Item.Key.Y, Item.Value->BaseType->GetPrimaryAssetId(), Item.Value->Data));
				}
			}

			for (TPair<FRPGItemSlot, URPGLoot*> Item: InventoryComponent->Equipement)
			{
				if (Item.Value)
				{
					CurrentSaveGame->SlottedItems.Add(Item.Key, FSaveStruct(-1, -1, Item.Value->BaseType->GetPrimaryAssetId(), Item.Value->Data));
				}
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
	UInventoryComponentC* InventoryComponent = GetInventoryComponent();
	if (InventoryComponent)
	{
		if (InventoryComponent->LoadInventory())
		{
			NotifyInventoryLoaded();
			return true;
		}
	}
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
			RefreshEffects();
			return true;
		}
	}
	return false;
}

UInventoryComponentC * ARPGPlayerControllerBase::GetInventoryComponent()
{
	return FindComponentByClass<UInventoryComponentC>();
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