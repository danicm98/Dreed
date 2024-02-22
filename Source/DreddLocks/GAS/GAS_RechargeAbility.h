// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GAS/GAS_GameplayAbilityBase.h"
#include "../GAS/GAS_RechargeEffect.h"
#include  "../GAS/GAS_EffectRechargeCalculation.h"
#include "GameplayEffect.h"
#include "GAS_RechargeAbility.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UGAS_RechargeAbility : public UGAS_GameplayAbilityBase
{
	GENERATED_BODY()

public:
	UGAS_RechargeAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> RechargeGameplayEffect;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void ThrowAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Bullets;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effect")
		const UGAS_RechargeEffect* Effect;
};
