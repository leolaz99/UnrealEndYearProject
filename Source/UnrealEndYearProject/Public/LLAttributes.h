#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLAttributes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, newVal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwnerDeath, bool, isAlive);


UCLASS( ClassGroup=(LL), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API ULLAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULLAttributes();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	UFUNCTION(BlueprintCallable, Category = LL)
	void RemoveHealth(const float value);

	UFUNCTION(BlueprintCallable, Category = LL)
	void SetHealth(const float value);

	UFUNCTION(BlueprintPure, Category = LL)
	float GetCurrentHealth() const 
	{
		return CurrentHealth;
	}

	UFUNCTION(BlueprintPure, Category = LL)
	float GetDamage() const
	{
		return Damage;
	}

	UFUNCTION(BlueprintPure, Category = LL)
	float GetIsAlive() const
	{
		return bIsAlive;
	}

	UFUNCTION(BlueprintCallable, Category = LL)
	void Kill() {
		bIsAlive = false;
	}

	UFUNCTION(BlueprintCallable, Category = LL)
	void Revive() {
		bIsAlive = true;
	}


	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnOwnerDeath OnOwnerDeath;

protected: 
	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

private: 
	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	bool bIsAlive;
};
