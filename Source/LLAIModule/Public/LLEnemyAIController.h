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
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void DetectPlayer(AActor* Player);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = LL)
	UBehaviorTree* behaviorTree;

	UBlackboardComponent* MyBlackboard;

	bool isSpotted;

	UPROPERTY(EditAnywhere, Category = LL)
	float attackRange;

	UPROPERTY(EditAnywhere, Category = LL)
	FName blackboardPlayer;

	UPROPERTY(EditAnywhere, Category = LL)
	FName blackboardHasSpottedPlayer;

	UPROPERTY(EditAnywhere, Category = LL)
	FName blackboardPlayerInRange;

public:
	virtual void Tick(float DeltaTime) override;
};