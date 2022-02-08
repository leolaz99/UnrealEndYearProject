#include "LLAttackPlayer.h"
#include "LLEnemy.h"
#include "AIController.h"

EBTNodeResult::Type ULLAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const AAIController* ownerController = OwnerComp.GetAIOwner();
	APawn* ownerPawn = ownerController->GetPawn();

	ALLEnemy* enemy = Cast<ALLEnemy>(ownerPawn);

	FTimerHandle TimerHandle;
	
	enemy->AttackPlayer();
	
	//delay

	return EBTNodeResult::Succeeded;
}
