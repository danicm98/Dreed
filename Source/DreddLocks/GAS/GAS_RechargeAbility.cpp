// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/GAS_RechargeAbility.h"
#include "../Dredd/DreddLocksCharacter.h"

UGAS_RechargeAbility::UGAS_RechargeAbility()
{
	AbilityInputID = ShootMode::Recharge;
	
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;


	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Recharge"));


	AbilityTags.AddTag(Ability1Tag);

	ActivationOwnedTags.AddTag(Ability1Tag);

}

void UGAS_RechargeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{




	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		//Si algo falla finaliza la habilidad
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	}

	ThrowAbility();
}

void UGAS_RechargeAbility::ThrowAbility()

{

	//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	const UGAS_RechargeEffect* GameplayEffect = NewObject<UGAS_RechargeEffect>();

	const UGAS_EffectRechargeCalculation* GameplayEffectCalc = NewObject<UGAS_EffectRechargeCalculation>();

	FGameplayEffectSpecHandle RechargeEffectSpecHandle = MakeOutgoingGameplayEffectSpec(RechargeGameplayEffect, GetAbilityLevel());

	//ApplyGameplayEf
	ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, RechargeEffectSpecHandle);
	//ApplyGameplayEffectToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, GameplayEffect, 5, 1);
	//RechargeEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Bullets")), Bullets);

	//Esto esta bien
	//ApplyGameplayEffectToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, GameplayEffect, 5, 1);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);




	//TSubclassOf<UGameplayEffect>& = Effect;
		
		//ApplyGameplayEffectSpecToOwner
		//ApplyGameplayEffectToOwner
		//ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, GameplayEffectCalc, 5, 1);
}
