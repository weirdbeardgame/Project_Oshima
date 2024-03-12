// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h" 
#include "Item.h"
#include "HorizontalItemSlot.generated.h"

// Should the slot know how many items there are? Or, is that the Inventory's job...
UCLASS()
class OSHIMA_API UHorizontalItemSlot : public UHorizontalBox
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UItem* itemContained;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UImage* itemIcon;
	
	// How many spaces does this take up
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int spaceSize;

	// For stacking
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int maxAmtStackable;	
	
	// For stacking
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int amtStacked;


public:
	UHorizontalItemSlot();

	bool AddItem(UItem* toAdd);

	UItem* UseItem();
	FString GetItemName() { return itemContained->GetItemName(); }
};
