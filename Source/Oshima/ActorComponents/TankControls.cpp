// Fill out your copyright notice in the Description page of Project Settings.


#include "TankControls.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/GameStateBase.h"

void UTankControls::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerDesiredRotation = true;
	RotationRate = FRotator(0.0f, rotationSpeed, 0.0f);
	MaxWalkSpeed = normalWalkSpeed;
}
 
void UTankControls::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float GetAxisDeltaRotation(float InAxisRotationRate, float DeltaTime)
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}

void UTankControls::PhysicsRotation(float deltaTime)
{
	FRotator deltaRot = FRotator(GetAxisDeltaRotation(RotationRate.Pitch, deltaTime), GetAxisDeltaRotation(RotationRate.Yaw, deltaTime), GetAxisDeltaRotation(RotationRate.Roll, deltaTime));
	FRotator currentRotation = UpdatedComponent->GetComponentRotation();
	FRotator DesiredRotation = CharacterOwner->Controller->GetDesiredRotation();

	FRotator RotationResult;

	const float AngleTolerance = 1e-3f;

	if (!currentRotation.Equals(DesiredRotation, AngleTolerance))
	{
		if (!FMath::IsNearlyEqual(currentRotation.Yaw, DesiredRotation.Yaw, AngleTolerance))
		{
			RotationResult.Yaw = FMath::FixedTurn(currentRotation.Yaw, DesiredRotation.Yaw, deltaRot.Yaw); //FMath::RInterpTo(currentRotation, DesiredRotation, deltaTime, rotationSpeed);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("RotRes: %s"), *RotationResult.ToString());

	DesiredRotation.DiagnosticCheckNaN(TEXT("CharacterMovementComponent::PhysicsRotation(): DesiredRotation"));
	CharacterOwner->SetActorRotation(RotationResult);
}

void UTankControls::PhysCustom(float deltaTime, int32 Iterations)
{
	if (CustomMovementMode == CustomMove::LADDER_CLIMB)
	{

	}

	//CalcVelocity(deltaTime, 0, false, false);
}

void UTankControls::Move(FVector2D vec, FVector forward, float rotation, APlayerController* PC)
{
	FVector2D inputVec;
	FVector direction = Velocity;

	direction.Normalize();

	// Walkest thou in reverse
	if (FVector::DotProduct(direction, forward) < 0.0)
	{
		MaxWalkSpeed = backwardsWalkSpeed;
	}
	else
	{
		MaxWalkSpeed = normalWalkSpeed;
	}

	inputVec += vec;

	AddInputVector(forward * inputVec.Y);
}

void UTankControls::StartClimb()
{
	SetMovementMode(EMovementMode::MOVE_Custom, CustomMove::LADDER_CLIMB);
}

void UTankControls::EndClimb()
{

}