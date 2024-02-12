// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankControls.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "CollisionDetect.generated.h"

USTRUCT(BlueprintType)
struct FLedgeProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FVector MaxLedgeHeight;

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FVector MinLedgeHeight;

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FVector WalkableDistance;

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FVector StepOffset;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OSHIMA_API UCollisionDetect : public UActorComponent
{
	GENERATED_BODY()

	FCollisionQueryParams CollideQueryParams;

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int CollisionCapsuleRadius = 50;

	UPROPERTY(Category = "Collision Properties", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int CollisionCapsuleHalfHeight = 72;

	
	// TRACE RESULTS
	FVector wallLocation;
	FVector wallNormal;

	float lowLege;
	float midLege;
	float highLege;


public:	
	// Sets default values for this component's properties
	UCollisionDetect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool MultiChannelSweep(FVector Start, FVector End, TArray<FHitResult> Hits, ECollisionChannel CollisionChan);

	UFUNCTION(BlueprintCallable)
	bool ShootRaycast(FVector Start, FVector End, FHitResult Hit, ECollisionChannel CollisionChan);

	UFUNCTION(BlueprintCallable)
	bool DetectWall(FVector Start, FVector End, UCharacterMovementComponent* move);

	UFUNCTION(BlueprintCallable)
	bool DetectLedge(FLedgeProperties ledge, UCharacterMovementComponent* move, FVector actorLocation);

	void SweepMultiple(TArray<FHitResult>& hits, ECollisionChannel chan, int numCapsules, double multiplier, FVector Start, FVector End, FVector Offset);

};
