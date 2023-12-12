// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class OSHIMA_API IMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual FString GetMenuName() = 0;
};
