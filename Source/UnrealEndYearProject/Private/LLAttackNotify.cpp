#include "LLAttackNotify.h"
#include "LLMeleeAttack.h"

void ULLAttackNotify::NotifyTick(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	enemy = Cast<ALLEnemy>(MeshComp->GetOwner());
	if (enemy) 
	{
		meleeAttack = enemy->FindComponentByClass<ULLMeleeAttack>();
		meleeAttack->Attack();
	}
	
}

void ULLAttackNotify::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	enemy = Cast<ALLEnemy>(MeshComp->GetOwner());
	if (enemy) 
	{
		meleeAttack = enemy->FindComponentByClass<ULLMeleeAttack>();
		meleeAttack->isDamaged = false;
	}	
}
