#include "LLPlayer.h"
#include "InteractableObject.h"

void AInteractableObject::InteractWithPlayer(bool value, AActor* player)
{
	ALLPlayer* actualPlayer = Cast<ALLPlayer>(player);

	if (actualPlayer)
		actualPlayer->PlayerInRange(value);
}