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

	if (Data.EvaluatedData.Attribute == GetChargerBasicBulletsAttribute()) {
		SetChargerBasicBullets(FMath::Clamp(GetChargerBasicBullets(), 0.0f, GetMaxChargerBasicBullets()));
	}
	if (Data.EvaluatedData.Attribute == GetTotalBasicBulletsAttribute()) {
		SetTotalBasicBullets(FMath::Clamp(GetTotalBasicBullets(), 0.0f, GetMaxTotalBasicBullets()));
	}

	

}

