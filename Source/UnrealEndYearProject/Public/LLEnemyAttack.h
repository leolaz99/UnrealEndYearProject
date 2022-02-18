#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLEnemyAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API ULLEnemyAttack : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULLEnemyAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
