// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "state.generated.h"
/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OSHIMA_API UState : public UActorComponent
{

	GENERATED_BODY()

private:

	FString stateName;
	bool isActive;
public:
	UState();
	virtual UState* UpdateState();
	virtual UState* GetInstance() { return this; }
	UFUNCTION(BlueprintCallable)
	virtual void Start();
	UFUNCTION(BlueprintCallable)
	virtual void Stop();
	UFUNCTION(BlueprintImplementableEvent)
	virtual void Update();
};
