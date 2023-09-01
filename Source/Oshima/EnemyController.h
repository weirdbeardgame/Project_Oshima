// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Health.h"
#include "ActorType.h"
#include "EnemyController.generated.h"

UCLASS()
class OSHIMA_API AEnemyController : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		class UHealth* health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		class UActorType* tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		FString EnemyName;

public:
	// Sets default values for this character's properties
	AEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
