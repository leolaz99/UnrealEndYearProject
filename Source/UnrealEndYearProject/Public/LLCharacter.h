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
	
	UPROPERTY(EditAnywhere)
	float normalSpeed;

	UPROPERTY(EditAnywhere)
	float sprintSpeed;

	UFUNCTION(BlueprintCallable, Category = LL)
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StopSprint();

	UFUNCTION(BlueprintCallable, Category = LL)
	void Rolling();

	UPROPERTY(EditAnywhere)
	float rollingDistance = 6000.f;

	UFUNCTION(BlueprintCallable, Category = LL)
	void StartAim();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StopAim();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool crouched;
};
