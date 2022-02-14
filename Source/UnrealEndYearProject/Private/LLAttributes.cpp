#include "LLAttributes.h"
#include "Components/CapsuleComponent.h"

ULLAttributes::ULLAttributes()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULLAttributes::BeginPlay()
{
	Super::BeginPlay();
}

void ULLAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULLAttributes::AddHealth(const float value)
{
	
}

void ULLAttributes::RemoveHealth(const float value)
{
	CurrentHealth -= value;
	OnHealthChanged.Broadcast(value);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Damage")));

	if (GetCurrentHealth() <= 0)
	{
		USkeletalMeshComponent* mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		UCapsuleComponent* capsule = GetOwner()->FindComponentByClass<UCapsuleComponent>();

		mesh->SetSimulatePhysics(true);
		capsule->DestroyComponent(true);

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("vita a 0")));
	}
}
