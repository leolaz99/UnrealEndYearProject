#include "LLRandomLocation.h"
#include "LLEnemyAIController.h"
#include "NavigationSystem.h"
#include "InputCoreTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type ULLRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();

	const AAIController* ownerController = OwnerComp.GetAIOwner();
	const APawn* ownerPawn = ownerController->GetPawn();
	
	FVector actorLocation = ownerPawn->GetActorLocation();

	if (OwnerComp.GetBlackboardComponent())
	{
		if (GetWorld())
		{
			UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());

			if (navSystem)
			{
				FVector startPos = actorLocation;
				FNavLocation endPos = FNavLocation(startPos);

				if (navSystem->GetRandomReachablePointInRadius(startPos, searchRadius, endPos))
				{
					blackBoard->SetValueAsVector(BlackboardTargetLocation, endPos.Location);		
				}
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}
