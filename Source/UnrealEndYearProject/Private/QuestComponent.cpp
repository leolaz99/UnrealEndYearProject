#include "QuestComponent.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	completedQuest = 0;
}

void UQuestComponent::IsCompleted(const int ID)
{
	FQuestParam* questpar = quest.Find(ID);
	if (questpar)
		questpar->isCompleted = true;

	OnQuestComplete.Broadcast(ID);

	completedQuest++;

	if(completedQuest == quest.Num())
		UGameplayStatics::OpenLevel(this, map);
}

void UQuestComponent::AddCounter(const int ID, const int ValueToAdd)
{
	FQuestParam* questpar = quest.Find(ID);

	if (questpar)
	{
		questpar->questCounter = questpar->questCounter + ValueToAdd;

		if (questpar->questCounter >= questpar->questTarget)
			IsCompleted(ID);
	}
}