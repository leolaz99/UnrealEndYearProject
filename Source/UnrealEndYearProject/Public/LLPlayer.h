#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "LLAttributes.h"
#include "LLBaseCharacter.h"
#include "LLPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS()
class UNREALENDYEARPROJECT_API ALLPlayer : public ALLBaseCharacter
{
	GENERATED_BODY()

public:
	ALLPlayer();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool crouched;

	bool aiming;

	bool sprinting;

	bool roll;

	void PlayerInRange(const bool NewValue);

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnInteract OnInteract;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveForward(const float verticalAxis);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveCameraVertical(const float axisValue);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveCameraHorizontal(const float axisValue);

	UFUNCTION(BlueprintCallable, Category = LL)
	void MoveHorizontal(const float horizontalAxis);

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckSprint(const float verticalAxisValue, const float horizontalAxisValue);

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

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckLost(FName Map);

	UFUNCTION(BlueprintCallable, Category = LL)
	void Interaction();

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool inRange;

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

	UPROPERTY(EditAnywhere)
	UAnimMontage* fireMontage;

private:

	UPROPERTY(EditAnywhere)
	USoundBase* ShootSound;
};
