// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalItemSlot.h"

UHorizontalItemSlot::UHorizontalItemSlot()
{
	itemIcon = CreateDefaultSubobject<UImage>("ItemIcon");
}

UItem* UHorizontalItemSlot::UseItem()
{
	// Issue is if we have mixables or something like that, we'll need two objects not a count of one instance!
	if (itemAmt > 0)
	{
		return itemContained;
	}
}