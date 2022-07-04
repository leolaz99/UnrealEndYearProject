#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamagable.h"
#include "LLBaseCharacter.h"
#include "LLEnemy.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLEnemy : public ALLBaseCharacter, public IIDamagable
{
	GENERATED_BODY()

public:
	
	ALLEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* attackPlayerMontage;

	UPROPERTY(blueprintReadOnly, EditAnywhere, Category = LLQuest)
	int id;

	UPROPERTY(blueprintReadOnly, EditAnywhere, Category = Save)
	int saveID;

public:	
	UFUNCTION(BlueprintCallable, Category = LL)
	void AttackPlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USoundBase* spottedSound;

	UPROPERTY(EditAnywhere)
	USoundBase* attackSound;
};
