#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "IInteractable.h"
#include "InteractableObject.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API AInteractableObject : public ATriggerBox, public IIInteractable
{
	GENERATED_BODY()
};
