#include "LLEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "LLCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ALLEnemyAIController::ALLEnemyAIController()
{
}

void ALLEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(behaviorTree);
}

void ALLEnemyAIController::DetectPlayer()
{
	TSubclassOf<ALLCharacter> classToFind;
	classToFind = ALLCharacter::StaticClass();
	TArray<AActor*> foundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);

	UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
	MyBlackboard->SetValueAsBool(blackboardHasSpottedPlayer, true);
	MyBlackboard->SetValueAsObject(blackboardPlayer, foundEnemies[0]);
}
