#include "BehaviorTree/BehaviorTree.h"
#include "LLEnemyAIController.h"
#include "LLCharacter.h"

ALLEnemyAIController::ALLEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> enemyBehaviorTreeObject(TEXT("BehaviorTree'/Game/Enemy/BehaviourTree/BT_Enemy.BT_Enemy'"));
	if (enemyBehaviorTreeObject.Succeeded())
		enemyBehaviorTree = enemyBehaviorTreeObject.Object;
}

void ALLEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(enemyBehaviorTree);
}

void ALLEnemyAIController::DetectPlayer(bool spotted)
{
	isSpotted = spotted;
}
