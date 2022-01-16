#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLAttributes.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API ULLAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULLAttributes();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float CurrentHealth;
};
