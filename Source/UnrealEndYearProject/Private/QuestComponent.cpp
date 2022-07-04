#include "QuestComponent.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	completedQuest = 0;
}

void UQuestComponent::IsCompleted(const int QuestIndex)
{
	if (quest.Num() > 0)
	{
		for (int i = 0; i < quest.Num(); i++)
		{
			if (quest[i].questIndex == QuestIndex)
			{
				quest[i].isCompleted = true;
				OnQuestComplete.Broadcast(QuestIndex);
				completedQuest++;
			}			
		}
	}

	if(completedQuest == quest.Num())
		UGameplayStatics::OpenLevel(this, map);
}

void UQuestComponent::AddCounter(const int QuestIndex, const int ValueToAdd)
{
	if (quest.Num() > 0)
	{
		for (int i = 0; i < quest.Num(); i++)
		{
			if (quest[i].questIndex == QuestIndex) 
			{
				quest[i].questCounter = quest[i].questCounter + ValueToAdd;
				OnValueChange.Broadcast(QuestIndex, quest[i].questCounter);
				
				if (quest[i].questCounter >= quest[i].questTarget)
					IsCompleted(QuestIndex);
			}
		}	
	}
}

void UQuestComponent::SetCounter(const int QuestIndex, const int newValue)
{
	if (quest.Num() > 0)
	{
		for (int i = 0; i < quest.Num(); i++)
		{
			if (quest[i].questIndex == QuestIndex)
			{
				quest[i].questCounter = newValue;
				OnValueChange.Broadcast(QuestIndex, quest[i].questCounter);

				if (quest[i].questCounter >= quest[i].questTarget)
					IsCompleted(QuestIndex);
			}
		}
	}
}

int32 UQuestComponent::SetQuestCounter(int arrayIndex, int32 newValue)
{
	quest[arrayIndex].questCounter = newValue;

	if(quest[arrayIndex].questCounter == quest[arrayIndex].questTarget)
	{
		IsCompleted(quest[arrayIndex].questIndex);
	}

	return quest[arrayIndex].questCounter;
}
