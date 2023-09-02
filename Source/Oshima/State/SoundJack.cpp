#include "SoundJack.h"
#include "../CharacterController.h"

// Sets default values
USoundJack::USoundJack()
{
}

// Called when the game starts or when spawned
void USoundJack::BeginPlay()
{
	Super::BeginPlay();
	ACharacterController* character = (ACharacterController*)GetOwner();
	SpringArmComp = character->GetSpringArm();
}

void USoundJack::Activate()
{
	// Do stuff with SpringArm, Do stuff with sound jacking enabler
}

void USoundJack::DeActivate()
{

}

// TODO: Grab player's previous state and return it when undoing the SoundJacking
UState* USoundJack::UpdateState()
{
	// return PrevPlayerState;
	return nullptr;
}