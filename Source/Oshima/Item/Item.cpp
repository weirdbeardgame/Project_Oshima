// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
}

void UItem::Use()
{
	if (isConsumeable)
	{
		switch (operationType)
		{
		case Operator::ADD:
			// Perform Add operation in here
			break;

		case Operator::SUBTRACT:
			// Perform Subtract operation in here
			break;
		}
	}
}
