#include "LLEnemyAttack.h"

ULLEnemyAttack::ULLEnemyAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULLEnemyAttack::BeginPlay()
{
	Super::BeginPlay();
}

void ULLEnemyAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

