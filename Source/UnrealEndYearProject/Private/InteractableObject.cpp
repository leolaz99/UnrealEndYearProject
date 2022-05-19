#include "LLCharacter.h"
#include "InteractableObject.h"

void AInteractableObject::InteractWithPlayer(bool value, AActor* player)
{
	ALLCharacter* actualPlayer = Cast<ALLCharacter>(player);

	if (actualPlayer)
		actualPlayer->PlayerInRange(value);
}
