// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

UState::UState()
{
}

void UState::Start()
{
	isActive = true;
}

UState* UState::UpdateState()
{
	UState* returnState = nullptr;
	// Inbetween's some logic that'll decide the next state
	return returnState;
}

void UState::Stop()
{
	isActive = false;

}

void UState::Update()
{

}

