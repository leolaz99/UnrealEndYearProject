#include "LLQuestSystem.h"

ALLQuestSystem::ALLQuestSystem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALLQuestSystem::IsCompleted(int ID)
{	
	quest.Add(ID, true);
}

void ALLQuestSystem::AddCounter(int ID, int ValueToAdd)
{
	int questValue = questCounter.FindOrAdd(ID);
	questValue = questValue + ValueToAdd;
	questCounter.Add(ID, questValue);

	int questCounterTarget = questTargetCounter.FindOrAdd(ID);

	if (questCounterTarget == questValue)
		IsCompleted(ID);
}