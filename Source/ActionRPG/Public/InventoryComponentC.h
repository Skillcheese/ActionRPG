// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGLoot.h"
#include "RPGGameInstanceBase.h"
#include "RPGAssetManager.h"
#include "RPGSaveGame.h"
#include "InventoryComponentC.generated.h"


UCLASS(BlueprintType, Blueprintable)
class ACTIONRPG_API UInventoryComponentC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponentC();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool LoadInventory();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Inventory)
	bool AddNewItemToInventory(URPGLoot* Item, URPGLoot* &RemainingItem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TMap<FIntPoint, URPGLoot*> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TMap<FRPGItemSlot, URPGLoot*> Equipement;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};