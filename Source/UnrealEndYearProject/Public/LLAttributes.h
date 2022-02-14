#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLAttributes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, newVal);

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
	void AddHealth(const float value);

	UFUNCTION(BlueprintCallable, Category = LL)
	void RemoveHealth(const float value);

	UFUNCTION(BlueprintPure, Category = LL)
	float GetCurrentHealth() const 
	{
		return CurrentHealth;
	}

	UPROPERTY(BlueprintAssignable, Category = LL)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(EditAnywhere)
	float Damage;

protected: 

	UPROPERTY(EditAnywhere)
	float CurrentHealth;
};
