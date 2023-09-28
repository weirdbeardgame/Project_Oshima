// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ActorComponents/TankControls.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterController::ACharacterController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UTankControls>(ACharacterController::CharacterMovementComponentName))
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    jacking = false; //sound mechanic boolean

	MovementComponent = Cast<UTankControls>(GetCharacterMovement());

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.0f;	
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	health = CreateDefaultSubobject<UHealth>(TEXT("Health"));
	health->SetDefaultHealth(300.00);

	tag = CreateDefaultSubobject<UActorType>(TEXT("ActorType"));
	tag->SetTag(ActorTypes::PLAYER);

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	collision = CreateDefaultSubobject< UCollisionDetect>(TEXT("CollisionDetctor"));
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DetectWall(MovementComponent->UpdatedComponent->GetForwardVector(), MovementComponent->UpdatedComponent->GetComponentLocation(), ECC_GameTraceChannel1))
	{
		UE_LOG(LogTemp, Warning, TEXT("WALL DETECTED"));
		if (DetectLedge(MovementComponent->UpdatedComponent->GetForwardVector(), MovementComponent->UpdatedComponent->GetComponentLocation(), ECC_GameTraceChannel1))
		{
			UE_LOG(LogTemp, Warning, TEXT("LEDGE DETECTED"));
		}
	}
}

bool ACharacterController::DetectWall(FVector Forward, FVector CurrentPosition, ECollisionChannel CollisionChan)
{
	FVector Start = (Forward * 20) + CurrentPosition;
	FVector End = Start + Forward;

	return collision->DetectWall(Start, End, GetCustomCharacterMovement());
}

bool ACharacterController::DetectLedge(FVector Forward, FVector CurrentPosition, ECollisionChannel CollisionChan)
{
	return collision->DetectLedge(LedgeProperties, GetCustomCharacterMovement(), GetActorLocation());
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterController::Look);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ACharacterController::GoProne);
	}
}

void ACharacterController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement 
		MovementComponent->Move(MovementVector, ForwardDirection, MovementVector.X, CastChecked<APlayerController>(Controller));
		AddControllerYawInput(MovementVector.X);
	}
}

void ACharacterController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if ((Controller != nullptr) && (jacking == false))
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacterController::GoProne(const FInputActionValue& Value)
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Crouched"));
		Crouch();
	}
}

void ACharacterController::EquipWeapon_Implementation(AWeapon* equip)
{
	if (currentWeapon != equip)
	{
		currentWeapon = equip;
	}
}

// Note that when we merge the StateMachine branch this will require logic for State stop and Start function call
void ACharacterController::UpdateState(TEnumAsByte <StateMachine> s)
{
	if (currentState != s)
	{
		currentState = s;
	}
}