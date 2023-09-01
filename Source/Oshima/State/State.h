// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "state.generated.h"
/**
 * 
 */

UCLASS()
class OSHIMA_API UState : public UObject
{

	GENERATED_BODY()

private:

	FString stateName;
	bool isActive;
public:
	UState();
	virtual void Activate();
	virtual void DeActivate();
};
