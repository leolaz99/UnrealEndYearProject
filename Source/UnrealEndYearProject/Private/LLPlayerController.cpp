#include "LLPlayerController.h"

void ALLPlayerController::AddEnemyID(const int32 id)
{
	enemyID.Add(id);
}

void ALLPlayerController::AddInteractableID(const int32 id)
{
	interactableID.Add(id);
}

void ALLPlayerController::AddPointOfInterestID(const int32 id)
{
	pointOfInterestID.Add(id);
}
