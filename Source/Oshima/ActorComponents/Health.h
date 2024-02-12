// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OSHIMA_API UHealth : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Stats")
		float maxHealth;

	float currentHealth;
public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetDefaultHealth(float val) {
		if (val > 0)
			maxHealth = val;
	}

	UFUNCTION(BlueprintCallable)
	float IncreaseHealth(float val);
	UFUNCTION(BlueprintCallable)
	float DecreaseHealth(float val);

	// These are meant for buffer effects like poison or anything like that. If we get that complex
	UFUNCTION(BlueprintCallable)
	float IncreaseMaxHealth(float val);
	UFUNCTION(BlueprintCallable)
	float DecreaseMaxHealth(float val);
	
	UFUNCTION(BlueprintCallable)
	void ResetHealth();
};
