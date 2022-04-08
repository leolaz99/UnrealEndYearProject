#include "LLMeleeAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "IDamagable.h"
#include "DrawDebugHelpers.h"

ULLMeleeAttack::ULLMeleeAttack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULLMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
	
	actorsToIgnore.Add(GetOwner());
	attributes = GetOwner()->FindComponentByClass<ULLAttributes>();
}

void ULLMeleeAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULLMeleeAttack::Attack()
{
	skeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SocketLocation1 = skeletalMesh->GetSocketLocation("lowerarm_r");
	SocketLocation2 = skeletalMesh->GetSocketLocation("middle_03_r");

	FCollisionQueryParams params;

	bool isHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), SocketLocation1, SocketLocation2, 5.f, UEngineTypes::ConvertToTraceType(ECC_Camera), false, actorsToIgnore, 
															EDrawDebugTrace::ForDuration, hitResult, true, FLinearColor::Red, FLinearColor::Green, 1.f);
	
	if (isHit)
	{
		IIDamagable* isDamagable = Cast<IIDamagable>(hitResult.Actor);

		if (!isDamaged && !isDamagable)
		{
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), attributes->Damage, NULL, NULL, NULL);
			isDamaged = true;
		}
	}
}

