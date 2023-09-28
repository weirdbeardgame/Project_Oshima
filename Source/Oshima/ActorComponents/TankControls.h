// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TankControls.generated.h"

UENUM()
enum CustomMove{NORMAL, LADDER_CLIMB, PRONE};

UCLASS()
class OSHIMA_API UTankControls : public UCharacterMovementComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float normalWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float backwardsWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float rotationSpeed;

private:
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PhysicsRotation(float DeltaTime) override;

	void Move(FVector2D vec, FVector forward, float rotation, APlayerController* PC);

	void StartClimb();
	void EndClimb();
};
