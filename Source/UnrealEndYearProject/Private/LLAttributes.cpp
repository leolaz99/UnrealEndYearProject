#include "LLAttributes.h"
#include "Components/CapsuleComponent.h"

ULLAttributes::ULLAttributes()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsAlive = true;
	MaxHealth = 1.f;
}

void ULLAttributes::BeginPlay()
{
	Super::BeginPlay();
}

void ULLAttributes::RemoveHealth(const float value)
{
	CurrentHealth -= value;
	OnHealthChanged.Broadcast(CurrentHealth);

	if (FMath::IsNearlyEqual(GetCurrentHealth(), 0, 0.001f) && bIsAlive)
	{
		USkeletalMeshComponent* mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		UCapsuleComponent* capsule = GetOwner()->FindComponentByClass<UCapsuleComponent>();

		mesh->SetSimulatePhysics(true);
		
		if (capsule != nullptr) {
			capsule->DestroyComponent(true);
		}

		bIsAlive = false;

		OnOwnerDeath.Broadcast(bIsAlive);
	}
}

void ULLAttributes::SetHealth(const float value)
{
	CurrentHealth = value;
	OnHealthChanged.Broadcast(CurrentHealth);
}
