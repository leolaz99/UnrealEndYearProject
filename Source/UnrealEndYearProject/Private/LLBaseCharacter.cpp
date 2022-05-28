#include "LLBaseCharacter.h"

ALLBaseCharacter::ALLBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALLBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALLBaseCharacter::TakeDamageMontage()
{
	if (damageMontage)
		PlayAnimMontage(damageMontage, 1.f, FName("Default"));
}

void ALLBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

