#include "LLMeleeAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LLPlayer.h"
#include "DrawDebugHelpers.h"

ULLMeleeAttack::ULLMeleeAttack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULLMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
	
	actorsToIgnore.Add(GetOwner());
	attributes = GetOwner()->FindComponentByClass<ULLAttributes>();
}

void ULLMeleeAttack::Attack()
{
	skeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SocketLocation1 = skeletalMesh->GetSocketLocation("lowerarm_r");
	SocketLocation2 = skeletalMesh->GetSocketLocation("middle_03_r");

	FCollisionQueryParams params;

	const bool isHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), SocketLocation1, SocketLocation2, 5.f, UEngineTypes::ConvertToTraceType(ECC_Camera), false, actorsToIgnore, 
															EDrawDebugTrace::ForDuration, hitResult, true, FLinearColor::Red, FLinearColor::Green, 1.f);
	
	if (isHit)
	{
		ALLPlayer* isPlayer = Cast<ALLPlayer>(hitResult.Actor);

		if (!isDamaged && isPlayer)
		{
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), attributes->GetDamage(), NULL, NULL, NULL);
			isDamaged = true;
		}
	}
}

