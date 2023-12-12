// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class OSHIMA_API UMenu : public UObject, public IMenuInterface
{
	GENERATED_BODY()
	
	FString MenuName;

public:
	virtual void Open() override;
	virtual void Close() override;

	virtual FString GetMenuName() override { return MenuName; }
};
