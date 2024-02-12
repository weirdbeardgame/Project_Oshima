// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDetect.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCollisionDetect::UCollisionDetect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionDetect::BeginPlay()
{
	Super::BeginPlay();

	CollideQueryParams.AddIgnoredActor(GetOwner());
	// ...
}

// Note that, the paramater Direction is the direction the raycast is starting from and facing
// * 20 is the length away from the player
bool UCollisionDetect::MultiChannelSweep(FVector Start, FVector End, TArray<FHitResult> Hits, ECollisionChannel CollisionChan)
{
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

	return GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity,
		CollisionChan, CollisionShape, CollideQueryParams);
}

bool UCollisionDetect::ShootRaycast(FVector Start, FVector End, FHitResult Hit, ECollisionChannel CollisionChan)
{
	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, CollisionChan, CollideQueryParams);
}

// Called every frame
void UCollisionDetect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollisionDetect::SweepMultiple(TArray<FHitResult>& hits, ECollisionChannel chan, int numCapsules, double multiplier, FVector Start, FVector End, FVector Offset)
{
	TArray<FHitResult> hitResult;
	//FVector STEP_OFFSET = FVector(-100, 0, 50);
	FVector currentStart = Start;
	FVector currentEnd = End;

	for (; numCapsules > 0; numCapsules--)
	{
		const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

		DrawDebugCapsule(GetWorld(), currentStart, CollisionCapsuleHalfHeight, CollisionCapsuleRadius, FQuat::Identity, FColor::Blue, 1.0f, 1.0f);

		if (GetWorld()->SweepMultiByChannel(hitResult, currentStart, currentEnd, FQuat::Identity, ECC_GameTraceChannel1, CollisionShape, CollideQueryParams))
		{
			hits += hitResult;
		}

		UE_LOG(LogTemp, Warning, TEXT("Position: %s"), *currentStart.ToString());
		currentStart += Offset;
		currentEnd += Offset;
	}
}

bool UCollisionDetect::DetectWall(FVector Start, FVector End, UCharacterMovementComponent* move)
{
	TArray<FHitResult> Hits;
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

	if (GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_GameTraceChannel1, CollisionShape, CollideQueryParams))
	{
		// We gotta wall ladies and gents!
		if (!move->IsWalkable(Hits[0]))
		{
			wallLocation = Hits[0].Location;
			wallNormal = Hits[0].ImpactNormal;
			return true;
		}
	}
	return false;
}

bool UCollisionDetect::DetectLedge(FLedgeProperties ledge, UCharacterMovementComponent* move, FVector actorLocation)
{
	TArray<FHitResult> hits;
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

	FVector Start = FVector(actorLocation.X, actorLocation.Y, ledge.MaxLedgeHeight.Z);

	// We gotta Ledge ladies and gents!

	SweepMultiple(hits, ECC_GameTraceChannel1, 5, 2, Start, ledge.MinLedgeHeight, ledge.StepOffset);

	for (auto& hit : hits)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));

		if (move->IsWalkable(hit))
		{
			FHitResult length;

			UE_LOG(LogTemp, Warning, TEXT("EL LEDGE"));

			DrawDebugLine(GetWorld(), ledge.MinLedgeHeight, ledge.WalkableDistance, FColor::Red);
			// Need to detect if is walkable on top or if there's at least room to stand.
			// Note that "End" is the start point. It's the point of contact with the base of the ledege detector
			if (ShootRaycast(ledge.MinLedgeHeight, ledge.WalkableDistance, length, ECC_GameTraceChannel1))
			{
				if (length.bBlockingHit)
				{
					return false;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("LEDGE DETECTED!"));
					return true;
				}
			}
		}
	}

	return false;
}