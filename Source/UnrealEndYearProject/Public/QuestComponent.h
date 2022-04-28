#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuestParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	bool isCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int questCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LL)
	int questTarget;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LL)
	TMap<int, FQuestParam> quest;

	UFUNCTION(BlueprintCallable, Category = LL)
	void IsCompleted(int ID);
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void AddCounter(int ID, int ValueToAdd);
};
