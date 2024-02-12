// Fill out your copyright notice in the Description page of Project Settings.

#include "DreddLocks/GAS/GASAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UGASAttributeSet::UGASAttributeSet() 
{
}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) {
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}

}

