#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::IsCompleted(int ID)
{
	quest.Add(ID, true);
}

void UQuestComponent::AddCounter(int ID, int ValueToAdd)
{
	int questValue = questCounter.FindOrAdd(ID);
	questValue = questValue + ValueToAdd;
	questCounter.Add(ID, questValue);

	int questCounterTarget = questTargetCounter.FindOrAdd(ID);

	if (questCounterTarget == questValue)
		IsCompleted(ID);
}

