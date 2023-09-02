// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine.h"

// Sets default values for this component's properties
UStateMachine::UStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStateMachine::ChangeState(UState* newState)
{
	if (currentState != nullptr)
	{
		if (newState != currentState)
		{
			currentState->DeActivate();
			delete(currentState);
			currentState = newState;
			return true;
		}
	}
	else
	{
		currentState = defaultS;
		return true;
	}
	return false;
}

bool UStateMachine::UpdateState(UState& state)
{
	if (ChangeState(&state))
	{
		printf("StateChanged, do stuffs in here");
		return true;
	}
	return false;
}