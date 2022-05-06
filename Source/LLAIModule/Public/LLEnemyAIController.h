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
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void DetectPlayer(AActor* Player);

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

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

private: 
	UFUNCTION()
	void OnPossessedCharacterDeath(bool bIsAlive);
};