#include "LLQuestBase.h"
#include "LLQuestSystem.h"
#include "Kismet/GameplayStatics.h"


ALLQuestBase::ALLQuestBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALLQuestBase::IsCompleted(int QuestID)
{
	AActor* questSystem = UGameplayStatics::GetActorOfClass(GetWorld(),ALLQuestSystem::StaticClass());
	ALLQuestSystem* actualquestSystem = Cast<ALLQuestSystem>(questSystem);

	actualquestSystem->quest.Add(QuestID, true);
}

void ALLQuestBase::AddCounter(int QuestID, int ValueToAdd)
{
	AActor* questSystem = UGameplayStatics::GetActorOfClass(GetWorld(), ALLQuestSystem::StaticClass());
	ALLQuestSystem* actualquestSystem = Cast<ALLQuestSystem>(questSystem);

	int questValue = actualquestSystem->questCounter.FindOrAdd(questID);
	questValue = questValue + ValueToAdd;
	actualquestSystem->questCounter.Add(QuestID, questValue);

	int questCounterTarget = actualquestSystem->questTargetCounter.FindOrAdd(questID);

	if (questCounterTarget == questValue)
		IsCompleted(QuestID);
}
