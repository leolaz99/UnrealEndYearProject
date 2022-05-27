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

	UPROPERTY(EditAnywhere)
	UAnimMontage* attackPlayerMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* damageMontage;

	UFUNCTION(BlueprintCallable, Category = LL)
	void TakeDamageMontage();

	UPROPERTY(blueprintReadOnly, EditAnywhere, Category = LLQuest)
	int id;

public:	
	UFUNCTION(BlueprintCallable, Category = LL)
	void AttackPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
