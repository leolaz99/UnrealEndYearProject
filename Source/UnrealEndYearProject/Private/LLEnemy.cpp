#include "LLEnemy.h"
#include "Kismet/GameplayStatics.h"

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

	if (attackSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), attackSound, GetActorLocation(), 1.f, 1.f, 0.f, NULL);
}

void ALLEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}