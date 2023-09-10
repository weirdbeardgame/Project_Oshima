// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "State.h"
#include "StateMachine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OSHIMA_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

	UState* currentState;

	UPROPERTY(EditAnywhere, Category = State)
	UState* defaultS;

public:	
	// Sets default values for this component's properties
	UStateMachine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Note: DO NOT CALL CHANGE STATE DIRECTLY, call UpdateState
	void ChangeState(UState* newState);
	bool UpdateState();
};
