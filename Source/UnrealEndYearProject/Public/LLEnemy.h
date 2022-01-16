#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamagable.h"
#include "LLEnemy.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLEnemy : public ACharacter, public IIDamagable
{
	GENERATED_BODY()

public:
	
	ALLEnemy();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
