#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "State.h"
#include "SoundJack.generated.h"

UCLASS()
class OSHIMA_API USoundJack : public UState
{
	GENERATED_BODY()

public:
	// Sets default values for this empty's properties
	USoundJack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class USpringArmComponent* SpringArmComp;

public:
	// Called every frame
	virtual UState* UpdateState() override;
	virtual USoundJack* GetInstance() override { return this; }
	virtual void Start() override;
	virtual void Stop() override;
	virtual void Update() override;
};
