#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LLTeams.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENDYEARPROJECT_API ULLTeams : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULLTeams();

	UPROPERTY(EditAnywhere, Category = LL)
	int team;
};
