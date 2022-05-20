#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuestParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	FText questText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	bool isCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int32 questCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int32 questTarget;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestComplete, int, QuestIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LL)
	TMap<int32, FQuestParam> quest;

	UPROPERTY(EditAnywhere, Category = LL)
	FName map;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	int completedQuest;

	UFUNCTION(BlueprintCallable, Category = LL)
	void IsCompleted(int ID);
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void AddCounter(int ID, int ValueToAdd);

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnQuestComplete OnQuestComplete;
};
