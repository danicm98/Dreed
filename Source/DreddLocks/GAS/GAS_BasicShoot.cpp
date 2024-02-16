// Fill out your copyright notice in the Description page of Project Settings.


#include "DreddLocks/GAS/GAS_BasicShoot.h"
#include "GameplayTagContainer.h"

UGAS_BasicShoot::UGAS_BasicShoot()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGAS_BasicShoot::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}

}
