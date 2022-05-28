#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LLBaseCharacter.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALLBaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* damageMontage;
	
	UFUNCTION(BlueprintCallable, Category = LL)
	void TakeDamageMontage();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
