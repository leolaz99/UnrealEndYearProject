#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "LLAttributes.h"
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
	void MoveForward(float verticalAxis);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveCameraVertical(float axisValue);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveCameraHorizontal(float axisValue);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveHorizontal(float horizontalAxis);

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckSprint(float verticalAxisValue, float horizontalAxisValue);

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float sensitivity;

	void StartCrouch();

	void StopCrouch();

	UFUNCTION(BlueprintCallable, Category = LL)
	void Crouching();
	
	UPROPERTY(EditAnywhere)
	float normalSpeed;

	UPROPERTY(EditAnywhere)
	float normalSensitivity;

	float normalFOV;

	UPROPERTY(EditAnywhere)
	float sprintSpeed;

	UPROPERTY(EditAnywhere)
	float aimingSpeed;

	UPROPERTY(EditAnywhere)
	float aimSensitivity;

	UPROPERTY(EditAnywhere)
	float aimFOV;

	UPROPERTY(EditAnywhere)
	float fovChangeSpeed;

	UFUNCTION(BlueprintCallable, Category = LL)
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StopSprint();

	UFUNCTION(BlueprintCallable, Category = LL)
	void Rolling();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StartAim();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StopAim();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = LL)
	void StopFire();

	void FireShot();

	UPROPERTY(EditAnywhere)
	float fireRate;

	UPROPERTY(EditAnywhere)
	float range;

	float actualVerticalAxis;
	float actualHorizontalAxis;

	FTimerHandle handle;

	APlayerCameraManager* PlayerCamera;
	USpringArmComponent* SpringArm;
	USkeletalMeshComponent* rifleRef;
	ULLAttributes* attributes;
	UAnimMontage* fireMontage;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool crouched;

	bool aiming;

	bool sprinting;

	bool roll;
};
