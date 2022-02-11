#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "LLCharacter.h"
#include "LLEnemyAIController.generated.h"

UCLASS()
class LLAIMODULE_API ALLEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALLEnemyAIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = LL)
	void DetectPlayer();

	UPROPERTY(EditAnywhere)
	UBehaviorTree* behaviorTree;

	UBlackboardComponent* MyBlackboard;

	bool isSpotted;

	UPROPERTY(EditAnywhere)
	float attackRange;

	UPROPERTY(EditAnywhere)
	FName blackboardPlayer;

	UPROPERTY(EditAnywhere)
	FName blackboardHasSpottedPlayer;

	UPROPERTY(EditAnywhere)
	FName blackboardPlayerInRange;

public:
	virtual void Tick(float DeltaTime) override;
};