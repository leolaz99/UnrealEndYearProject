#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LLProjectile.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ALLProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
