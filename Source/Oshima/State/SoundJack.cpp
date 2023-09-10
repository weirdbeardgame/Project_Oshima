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

void USoundJack::Start()
{
	// Do stuff with SpringArm, Do stuff with sound jacking enabler
}

void USoundJack::Stop()
{

}

// TODO: Grab player's previous state and return it when undoing the SoundJacking
UState* USoundJack::UpdateState()
{
	// return PrevPlayerState;
	return nullptr;
}

void USoundJack::Update()
{
	// If there's any extra logic handle that needs to be in here?
}