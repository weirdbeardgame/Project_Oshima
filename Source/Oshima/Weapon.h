// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h" 
#include "Components/SkeletalMeshComponent.h" 
#include "Weapon.generated.h"

UCLASS()
class OSHIMA_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
		FString WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
		FString WeaponDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
		float Damage;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponData", meta = (AllowPrivateAccess = "true"))
		float RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
		UAudioComponent* audio;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* skeleMan;

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();

	UFUNCTION(BlueprintImplementableEvent)
	void Equip();

};
