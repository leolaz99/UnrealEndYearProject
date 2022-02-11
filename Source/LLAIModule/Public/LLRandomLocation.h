#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LLRandomLocation.generated.h"

UCLASS()
class LLAIMODULE_API ULLRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float searchRadius;

	UPROPERTY(EditAnywhere)
	FName BlackboardTargetLocation;
};
