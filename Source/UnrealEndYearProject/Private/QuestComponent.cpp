#include "Kismet/GameplayStatics.h"
#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	completedQuest = 0;
}

void UQuestComponent::IsCompleted(int ID)
{
	FQuestParam* questpar = quest.Find(ID);
	if (questpar)
		questpar->isCompleted = true;

	OnQuestComplete.Broadcast(ID);

	completedQuest++;

	if(completedQuest == quest.Num())
		UGameplayStatics::OpenLevel(this, map);
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