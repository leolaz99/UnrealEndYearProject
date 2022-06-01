#include "LLEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "LLPlayer.h"
#include "LLEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LLAttributes.h"

ALLEnemyAIController::ALLEnemyAIController()
{
}

void ALLEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(behaviorTree);
	MyBlackboard = GetBlackboardComponent();
}

void ALLEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn)
	{
		ULLAttributes * attComponent = InPawn->FindComponentByClass<ULLAttributes>();
		
		if (attComponent) 
			attComponent->OnOwnerDeath.AddDynamic(this, &ALLEnemyAIController::OnPossessedCharacterDeath);
	}
}

void ALLEnemyAIController::OnUnPossess()
{
	const APawn* InPawn = GetPawn();
	if (InPawn) 
	{
		ULLAttributes* attComponent = InPawn->FindComponentByClass<ULLAttributes>();
		
		if (attComponent)
			attComponent->OnOwnerDeath.RemoveDynamic(this, &ALLEnemyAIController::OnPossessedCharacterDeath);	
	}

	Super::OnUnPossess();
}

void ALLEnemyAIController::DetectPlayer(AActor* Player)
{
	const ALLPlayer* foundPlayer = Cast<ALLPlayer>(Player);

	if(foundPlayer && foundPlayer!= MyBlackboard->GetValueAsObject(blackboardPlayer))
	{
		const APawn* controlledPawn = GetPawn();
		const ALLEnemy* enemy = Cast<ALLEnemy>(controlledPawn);

		if (enemy->spottedSound)
			UGameplayStatics::PlaySound2D(GetWorld(), enemy->spottedSound, 1.f, 1.f, 0.f, NULL);
		
		MyBlackboard->SetValueAsBool(blackboardHasSpottedPlayer, true);
		MyBlackboard->SetValueAsObject(blackboardPlayer, Player);
	}
}

void ALLEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const APawn* controlledPawn = GetPawn();
	const float distanceToPlayer = controlledPawn->GetDistanceTo(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (MyBlackboard->GetValueAsBool(blackboardHasSpottedPlayer) == true)
	{
		if (distanceToPlayer <= attackRange)
			MyBlackboard->SetValueAsBool(blackboardPlayerInRange, true);
		
		else
			MyBlackboard->SetValueAsBool(blackboardPlayerInRange, false);
	}
}

void ALLEnemyAIController::OnPossessedCharacterDeath(bool bIsAlive)
{
	if (!bIsAlive ) 
	{
		UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
		
		if (BTComp)
			BTComp->StopTree(EBTStopMode::Safe);
	}
}
