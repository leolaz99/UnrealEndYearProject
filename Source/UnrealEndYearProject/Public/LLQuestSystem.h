#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LLQuestSystem.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLQuestSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALLQuestSystem();

	UPROPERTY(EditAnywhere)
	TMap<int, bool> quest;

	UPROPERTY(EditAnywhere)
	TMap<int, int> questCounter;

	UPROPERTY(EditAnywhere)
	TMap<int, int> questTargetCounter;
};
