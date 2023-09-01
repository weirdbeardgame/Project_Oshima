// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorType.generated.h"

UENUM()
enum class ActorTypes { PLAYER, ENEMY, NPC };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OSHIMA_API UActorType : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		ActorTypes tag;

public:	
	// Sets default values for this component's properties
	UActorType();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTag(ActorTypes t) {
		if (t != tag)
		{
			tag = t;
		}
	}

	ActorTypes GetTag() { return tag; }
		
};
