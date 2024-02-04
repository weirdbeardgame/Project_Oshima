// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ActorComponents/Health.h"
#include "ActorComponents/ActorType.h"
#include "ActorComponents/TankControls.h"
#include "ActorComponents/CollisionDetect.h"
#include "Weapon.h"
#include "CharacterController.generated.h"


UENUM()
enum class StateMachine {LADDER, NORMAL, LOW_HEALTH, DEAD, SOUNDJACKING};

UCLASS(config = Game)
class OSHIMA_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

	// Input mapping stuffs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	// Status and other objects	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		AWeapon *currentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		class UHealth* health;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		class UCollisionDetect* collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		class UActorType* tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
		FString CharacterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		StateMachine currentState;

	// Camera stuff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
        FLedgeProperties LedgeProperties;


public:
	// Sets default values for this character's properties
	ACharacterController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool jacking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UTankControls* MovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE UTankControls* GetCustomCharacterMovement() const { return MovementComponent; }

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void GoProne(const FInputActionValue& Value);

	bool DetectWall(FVector Forward, FVector CurrentPosition, ECollisionChannel CollisionChan);

	UFUNCTION(BlueprintCallable)
	bool DetectLedge(FVector Forward, FVector CurrentPosition, ECollisionChannel CollisionChan);

	UFUNCTION(BlueprintCallable)
	void UpdateState(TEnumAsByte <StateMachine> s);

	UFUNCTION(BlueprintNativeEvent)
	void EquipWeapon(AWeapon* weap);
};
