// Fill out your copyright notice in the Description page of Project Settings.


#include "../Enemies/GAS_EnemyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UGAS_EnemyAttributeSet::UGAS_EnemyAttributeSet()
{
}

void UGAS_EnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetEnemyHealthAttribute()) {
		SetEnemyHealth(FMath::Clamp(GetEnemyHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetArmorAttribute()) {
		SetArmor(FMath::Clamp(GetArmor(), 0.0f, GetMaxArmor()));
	}



}
