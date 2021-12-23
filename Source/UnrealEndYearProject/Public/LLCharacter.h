#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LLCharacter.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALLCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = LL)
		void MoveForward(float value);

	UFUNCTION(BlueprintCallable, Category = LL)
		void MoveHorizontal(float value);

	void StartCrouch();

	void StopCrouch();

	UFUNCTION(BlueprintCallable, Category = LL)
	void Crouching();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
