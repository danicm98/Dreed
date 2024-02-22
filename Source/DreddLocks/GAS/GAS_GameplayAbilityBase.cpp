// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/GAS_GameplayAbilityBase.h"
#include "GameplayTagContainer.h"

UGAS_GameplayAbilityBase::UGAS_GameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGAS_GameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{

	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
