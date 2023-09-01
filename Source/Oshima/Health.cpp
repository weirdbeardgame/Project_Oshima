// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealth::DecreaseHealth(float val)
{
	if ((currentHealth - val) >= 0)
	{
		return currentHealth -= val;
	}

	return 0;
}

float UHealth::IncreaseHealth(float val)
{
	if ((currentHealth + val) <= maxHealth)
	{
		return currentHealth += val;
	}

	return 0;
}

float UHealth::DecreaseMaxHealth(float val)
{
	if ((maxHealth - val) >= 0)
	{
		return maxHealth -= val;
	}

	return 0;
}

float UHealth::IncreaseMaxHealth(float val)
{
	return maxHealth += val;
}

void UHealth::ResetHealth()
{
	currentHealth = maxHealth;
}