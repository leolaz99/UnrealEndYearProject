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
	MyBlackboard = GetBlackboardComponent();
}

void ALLEnemyAIController::DetectPlayer()
{
	TSubclassOf<ALLCharacter> classToFind;
	classToFind = ALLCharacter::StaticClass();
	TArray<AActor*> foundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);

	MyBlackboard->SetValueAsBool(blackboardHasSpottedPlayer, true);
	MyBlackboard->SetValueAsObject(blackboardPlayer, foundEnemies[0]);
}

void ALLEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const APawn* controlledPawn = GetPawn();
	const float distanceToPlayer = controlledPawn->GetDistanceTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if(distanceToPlayer <= attackRange)
		MyBlackboard->SetValueAsBool(blackboardPlayerInRange, true);
	else
		MyBlackboard->SetValueAsBool(blackboardPlayerInRange, false);
}
