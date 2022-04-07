#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LLQuestBase.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLQuestBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ALLQuestBase();

protected:
	UFUNCTION(BlueprintCallable, Category = LL)
	void IsCompleted(int QuestID);

	UFUNCTION(BlueprintCallable, Category = LL)
	void AddCounter(int QuestID, int ValueToAdd);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int questID;
};
