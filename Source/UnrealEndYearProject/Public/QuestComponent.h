#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuestParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int32 questIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	FText questText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	bool isCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int32 questCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int32 questTarget;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestComplete, int32, QuestIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChange, int32, QuestIndex, int32, QuestCounter);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LL)
	TArray<FQuestParam> quest;

public:	
	UQuestComponent();

	UPROPERTY(EditAnywhere, Category = LL)
	FName map;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	int completedQuest;

	UFUNCTION(BlueprintCallable, Category = LL)
	void IsCompleted(const int ID);
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void AddCounter(const int QuestIndex, const int ValueToAdd);

	UFUNCTION(BlueprintCallable, Category = LL)
	void SetCounter(const int QuestIndex, const int newValue);

	UFUNCTION(BlueprintCallable, Category = LL)
	int32 GetQuestCounter(const int arrayIndex)
	{
		return quest[arrayIndex].questCounter;
	}

	UFUNCTION(BlueprintCallable, Category = LL)
	int GetQuestLenght()
	{
		return quest.Num();
	}

	UFUNCTION(BlueprintCallable, Category = LL)
	int GetQuestKey(int arrayElement)
	{
		return quest[arrayElement].questIndex;
	}

	UFUNCTION(BlueprintCallable, Category = LL)
	int32 SetQuestCounter(int arrayIndex, int32 newValue)
	{
		return quest[arrayIndex].questCounter = newValue;
	}

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnQuestComplete OnQuestComplete;

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnValueChange OnValueChange;
};
