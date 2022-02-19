#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LLEnemy.h"
#include "LLMeleeAttack.h"
#include "LLAttackNotify.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
		virtual void NotifyTick(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float FrameDeltaTime) override;
		
		virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;

		ALLEnemy* enemy;
		ULLMeleeAttack* meleeAttack;
};
