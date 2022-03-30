#pragma once

#include "CoreMinimal.h"
#include "LLEnemy.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LLAttackPlayer.generated.h"

UCLASS()
class LLAIMODULE_API ULLAttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UFUNCTION()
	void HandleMontageEnded(UAnimMontage* animMontage, bool finished);

	UBehaviorTreeComponent* behaviourTree;

	ALLEnemy* enemy;

	bool isStart = false;
};
