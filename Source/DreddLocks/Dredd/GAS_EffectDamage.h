// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GAS_EffectDamage.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UGAS_EffectDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

		
public:
	UGAS_EffectDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	
};
