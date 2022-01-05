#include "LLProjectile.h"

ALLProjectile::ALLProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALLProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ALLProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

