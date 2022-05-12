#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::IsCompleted(int ID)
{
	FQuestParam* questpar = quest.Find(ID);
	if (questpar)
		questpar->isCompleted = true;

	OnQuestComplete.Broadcast(ID);
}

void UQuestComponent::AddCounter(int ID, int ValueToAdd)
{
	FQuestParam* questpar = quest.Find(ID);

	if (questpar)
	{
		questpar->questCounter = questpar->questCounter + ValueToAdd;

		if (questpar->questCounter >= questpar->questTarget)
			IsCompleted(ID);
	}
}