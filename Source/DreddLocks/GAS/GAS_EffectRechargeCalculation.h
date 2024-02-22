// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GAS_EffectRechargeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UGAS_EffectRechargeCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UGAS_EffectRechargeCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
