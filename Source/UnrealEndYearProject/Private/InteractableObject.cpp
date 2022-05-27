#include "InteractableObject.h"
#include "LLPlayer.h"

void AInteractableObject::InteractWithPlayer(const bool value, AActor* player)
{
	ALLPlayer* actualPlayer = Cast<ALLPlayer>(player);

	if (actualPlayer)
		actualPlayer->PlayerInRange(value);
}