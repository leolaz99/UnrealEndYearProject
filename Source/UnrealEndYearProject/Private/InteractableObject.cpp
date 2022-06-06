#include "InteractableObject.h"
#include "LLPlayer.h"

bool AInteractableObject::InteractWithPlayer(const bool value, AActor* player)
{
	ALLPlayer* actualPlayer = Cast<ALLPlayer>(player);

	if (actualPlayer) 
	{
		actualPlayer->PlayerInRange(value);
		return true;
	}

	else
		return false;
}