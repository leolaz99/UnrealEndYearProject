#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int, bool> quest;

	UPROPERTY(EditAnywhere)
	TMap<int, int> questCounter;

	UPROPERTY(EditAnywhere)
	TMap<int, int> questTargetCounter;

	UFUNCTION(BlueprintCallable, Category = LL)
	void IsCompleted(int ID);

	UFUNCTION(BlueprintCallable, Category = LL)
	void AddCounter(int ID, int ValueToAdd);
};
