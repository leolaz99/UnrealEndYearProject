#include "BehaviorTree/BehaviorTree.h"
#include "LLEnemyAIController.h"
#include "LLCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

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

void ALLEnemyAIController::DetectPlayer()
{
	TSubclassOf<ALLCharacter> classToFind;
	classToFind = ALLCharacter::StaticClass();
	TArray<AActor*> foundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);

	UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
	MyBlackboard->SetValueAsBool(FName("HasSpottedPlayer"), true);
	MyBlackboard->SetValueAsObject(FName("Player"), foundEnemies[0]);
}
