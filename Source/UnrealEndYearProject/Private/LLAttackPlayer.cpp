#include "LLAttackPlayer.h"
#include "LLEnemy.h"
#include "AIController.h"

EBTNodeResult::Type ULLAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	behaviourTree = &OwnerComp;
	const AAIController* ownerController = OwnerComp.GetAIOwner();
	APawn* ownerPawn = ownerController->GetPawn();

	enemy = Cast<ALLEnemy>(ownerPawn);
	
	enemy->AttackPlayer();
	
	UAnimInstance* anim = enemy->GetMesh()->GetAnimInstance();

	anim->OnMontageEnded.AddDynamic(this, &ULLAttackPlayer::HandleMontageEnded);

	return EBTNodeResult::InProgress;
}

void ULLAttackPlayer::HandleMontageEnded(UAnimMontage* animMontage, bool finished)
{
	UAnimInstance* anim = enemy->GetMesh()->GetAnimInstance();
	anim->OnMontageEnded.RemoveAll(this);
	FinishLatentTask(*behaviourTree, EBTNodeResult::Succeeded);
}
