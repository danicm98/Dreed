// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/GAS_RechargeEffect.h"
#include "../Dredd/DreddLocksCharacter.h"
#include "DreddLocks/GAS/GASAttributeSet.h"
#include "GAS_EffectRechargeCalculation.h"
#include <Kismet/GameplayStatics.h>

UGAS_RechargeEffect::UGAS_RechargeEffect()
{




	//UGAS_EffectRechargeCalculation* MyCalculationClass = NewObject<UGAS_EffectRechargeCalculation>(this, UGAS_EffectRechargeCalculation::StaticClass());
	//MyCalculationClass->ConditionalBeginDestroy();  // Marca el objeto para destrucción, ya que UGameplayEffectExecutionCalculation no se destruye automáticamente.

	//Executions.Add(MyCalculationClass);


	//this->Executions.Add(MyCalculationClass);


	/*
	
	FGameplayModifierInfo DamageInfo;
	DamageInfo.Attribute = UGASAttributeSet::GetChargerBasicBulletsAttribute();
	DamageInfo.ModifierOp = EGameplayModOp::Additive;

	
	APawn* PlayerPawn;
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ADreddLocksCharacter* Player = Cast<ADreddLocksCharacter>(PlayerPawn);

	const UGASAttributeSet* AttributeSet = Player->GetAbilitySystemComponent()->GetSet<UGASAttributeSet>();
	float n ;

	if (AttributeSet)
	{

		float CurrentHealth = AttributeSet->GetHealth();

		if(CurrentHealth > 100){
			n = 5.f;

		{
		if (CurrentHealth <= 100) {
			n = .f;
		
		}


	}
	
	




	//float value = UGASAttributeSet::GetHealt;
	
	
	

	
	DamageInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(n);

	
	Modifiers.Add(DamageInfo);

	*/
}
