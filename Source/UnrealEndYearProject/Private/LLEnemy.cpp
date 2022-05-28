#include "LLEnemy.h"

ALLEnemy::ALLEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALLEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ALLEnemy::AttackPlayer()
{
	if(attackPlayerMontage != nullptr)
		PlayAnimMontage(attackPlayerMontage, 1.5f, FName("Default"));
}

void ALLEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}