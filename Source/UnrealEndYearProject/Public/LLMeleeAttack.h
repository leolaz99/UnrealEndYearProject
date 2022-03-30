#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLAttributes.h"
#include "LLTeams.h"
#include "LLMeleeAttack.generated.h"



UCLASS( ClassGroup=(LL), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API ULLMeleeAttack : public UActorComponent
{
	GENERATED_BODY()

public:		
	ULLMeleeAttack();

protected:
	virtual void BeginPlay() override;

	USkeletalMeshComponent* skeletalMesh;

	FVector SocketLocation1;
	FVector SocketLocation2;
	TArray<AActor*> actorsToIgnore;
	FHitResult hitResult;
	ULLAttributes* attributes;
	ULLTeams* team;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack();

	bool isDamaged;
};
