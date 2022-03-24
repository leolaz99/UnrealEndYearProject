#include "LLEnemy.h"

ALLEnemy::ALLEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALLEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ALLEnemy::TakeDamageMontage()
{
	if(damageMontage)
		PlayAnimMontage(damageMontage, 1.f, FName("Default"));
}

void ALLEnemy::AttackPlayer()
{
	if(attackPlayerMontage != nullptr)
		PlayAnimMontage(attackPlayerMontage, 1.5f, FName("Default"));
}

void ALLEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALLEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}