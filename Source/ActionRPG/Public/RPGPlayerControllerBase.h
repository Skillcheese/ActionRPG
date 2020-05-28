// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameFramework/PlayerController.h"
#include "RPGInventoryInterface.h"
#include "Items/RPGLoot.h"
#include "SkillNodeBase.h"
#include "RPGCharacterBase.h"
#include "RPGPlayerControllerBase.generated.h"

/** Base class for PlayerController, should be blueprinted */
UCLASS()
class ACTIONRPG_API ARPGPlayerControllerBase : public APlayerController, public IRPGInventoryInterface
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	ARPGPlayerControllerBase() {}
	virtual void BeginPlay() override;
	virtual void Possess(APawn* NewPawn) override;
	virtual void UnPossess() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<URPGLoot*> InventoryItems;

	/** Map of slot, from type/num to item, initialized from ItemSlotsPerType on RPGGameInstanceBase */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FRPGItemSlot, URPGLoot*> SlottedItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkillTree)
	TArray<USkillNodeBase*> SkillNodesTaken;

	/** Delegate called when an inventory item has been added or removed */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryItemChanged OnInventoryItemChanged;

	/** Native version above, called before BP delegate */
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	/** Delegate called when an inventory slot has changed */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSlottedItemChanged OnSlottedItemChanged;

	/** Called after the inventory was changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, URPGLoot* Item);

	/** Called after an item was equipped and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void SlottedItemChanged(FRPGItemSlot ItemSlot, URPGLoot* Item);

	/** Native version above, called before BP delegate */
	FOnSlottedItemChangedNative OnSlottedItemChangedNative;

	/** Delegate called when the inventory has been loaded/reloaded */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryLoaded OnInventoryLoaded;

	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSkillTreeLoaded OnSkillTreeLoaded;

	/** Native version above, called before BP delegate */
	FOnInventoryLoadedNative OnInventoryLoadedNative;
	FOnSkillTreeLoadedNative OnSkillTreeLoadedNative;

	/** Called right after we have possessed a pawn */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "BeginPossessPawn"))
	void ReceivePossess(APawn* NewPawn);

	/** Called right before unpossessing a pawn */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EndPossessPawn"))
	void ReceiveUnPossess(APawn* PreviousPawn);

	/** Adds a new inventory item, will add it to an empty slot if possible. If the item supports count you can add more than one count. It will also update the level when adding if required */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(URPGLoot* NewItem, int32 count = 1,  bool bAutoSlot = true);

	/** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(URPGLoot* RemovedItem, int32 RemoveCount = 1);

	UFUNCTION(BlueprintCallable, Category = SkillTree)
	int32 SetSkillNodeTaken(USkillNodeBase* SkillNode, bool Taken);

	/** Returns all inventory items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetInventoryItems(TArray<URPGLoot*>& Items, FPrimaryAssetType ItemType);

	UFUNCTION(BlueprintCallable, Category = SkillTree)
	TArray<USkillNodeBase*> GetSkillNodesTaken();

	UFUNCTION(BlueprintCallable, Category = Affix)
	TMap<TSubclassOf<UGE_Affix>, int32> GetInventoryItemAffixes(URPGLoot* Item, TMap<TSubclassOf<UGE_Affix>, int32> &PrefixMap, TMap<TSubclassOf<UGE_Affix>, int32> &SuffixMap, TMap<TSubclassOf<UGE_Affix>, int32> &ImplicitMap, TMap<TSubclassOf<UGE_Affix>, int32> &EnchantMap);

	UFUNCTION(BlueprintCallable, Category = Affix)
	bool UpdateItemAffixes(URPGLoot* Item, TMap<TSubclassOf<UGE_Affix>, int32> PrefixMap, TMap<TSubclassOf<UGE_Affix>, int32> SuffixMap, TMap<TSubclassOf<UGE_Affix>, int32> ImplicitMap, TMap<TSubclassOf<UGE_Affix>, int32> EnchantMap);

	/** Sets slot to item, will remove from other slots if necessary. If passing null this will empty the slot */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SetSlottedItem(FRPGItemSlot ItemSlot, URPGLoot* Item);

	/** Returns item in slot, or null if empty */
	UFUNCTION(BlueprintPure, Category = Inventory)
	URPGLoot* GetSlottedItem(FRPGItemSlot ItemSlot);

	UFUNCTION(BlueprintPure, Category = Souls)
	URPGLoot* GetSouls(int32 &Count);

	UFUNCTION(BlueprintPure, Category = Souls)
	URPGLoot* GetSoulsItem();

	UFUNCTION(BlueprintCallable, Category = Souls)
	bool AddSouls(int32 amount, int32 &Count);

	UFUNCTION(BlueprintImplementableEvent, Category = Souls)
	void SoulsChange();

	UFUNCTION(BlueprintCallable, Category = Souls)
	bool SoulsPurchase(int32 amount, int32 &Count);

	/** Fills in any empty slots with items in inventory */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void FillEmptySlots();

	/** Manually save the inventory, this is called from add/remove functions automatically */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SaveInventory();

	UFUNCTION(BlueprintCallable, Category = Character)
	bool RefreshEffects();

	/** Loads inventory from save game on game instance, this will replace arrays */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool LoadInventory();

	/** Loads inventory from save game on game instance, this will replace arrays */
	UFUNCTION(BlueprintCallable, Category = SkillTree)
	bool LoadSkillTree();

	// Implement IRPGInventoryInterface
	virtual const TArray<URPGLoot*>& GetInventory() const override
	{
		return InventoryItems;
	}
	virtual const TMap<FRPGItemSlot, URPGLoot*>& GetSlottedItemMap() const override
	{
		return SlottedItems;
	}
	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
	{
		return OnInventoryItemChangedNative;
	}
	virtual FOnSlottedItemChangedNative& GetSlottedItemChangedDelegate() override
	{
		return OnSlottedItemChangedNative;
	}
	virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() override
	{
		return OnInventoryLoadedNative;
	}

protected:
	/** Auto slots a specific item, returns true if anything changed */
	bool FillEmptySlotWithItem(URPGLoot* NewItem);

	/** Calls the inventory update callbacks */
	void NotifyInventoryItemChanged(bool bAdded, URPGLoot* Item);
	void NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGLoot* Item);
	void NotifyInventoryLoaded();
	void NotifySkillTreeLoaded();
};
