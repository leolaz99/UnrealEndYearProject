#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "LLCharacter.h"
#include "LLEnemyAIController.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALLEnemyAIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = LL)
	void DetectPlayer();

	UBehaviorTree* enemyBehaviorTree;

	bool isSpotted;
};