#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::IsCompleted(int ID)
{
	FQuestParam questpar = quest.FindOrAdd(ID);
	questpar.isCompleted = true;
}

void UQuestComponent::AddCounter(int ID, int ValueToAdd)
{
	FQuestParam questpar = quest.FindOrAdd(ID);
	questpar.questCounter = questpar.questCounter + ValueToAdd;
	
	if (questpar.questCounter >= questpar.questTarget)
		questpar.isCompleted = true;
}