// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/GAS_EffectRechargeCalculation.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "DreddLocks/GAS/GASAttributeSet.h"


struct GDRechargeStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(ChargerBasicBullets);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxChargerBasicBullets);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TotalBasicBullets);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxTotalBasicBullets);

	GDRechargeStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MaxChargerBasicBullets, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MaxTotalBasicBullets, Source, true);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, ChargerBasicBullets, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, TotalBasicBullets, Target, false);


	}


};
static const GDRechargeStatics& RechargeStatics()
{
	static GDRechargeStatics DStatics;
	return DStatics;
}

UGAS_EffectRechargeCalculation::UGAS_EffectRechargeCalculation()
{
	RelevantAttributesToCapture.Add(RechargeStatics().ChargerBasicBulletsDef);
	RelevantAttributesToCapture.Add(RechargeStatics().MaxChargerBasicBulletsDef);
	RelevantAttributesToCapture.Add(RechargeStatics().TotalBasicBulletsDef);
	RelevantAttributesToCapture.Add(RechargeStatics().MaxTotalBasicBulletsDef);
}

void UGAS_EffectRechargeCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float ChargerBasicBullets = 0.0f;
	float MaxChargerBasicBullets = 0.0f;
	float TotalBasicBullets = 0.0f;

	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RechargeStatics().ChargerBasicBulletsDef, EvaluationParameters, ChargerBasicBullets);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RechargeStatics().MaxChargerBasicBulletsDef, EvaluationParameters, MaxChargerBasicBullets);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RechargeStatics().TotalBasicBulletsDef, EvaluationParameters, TotalBasicBullets);

	float bulletToRecharge = MaxChargerBasicBullets  - ChargerBasicBullets;

	if (TotalBasicBullets - bulletToRecharge >= 0 ) {

		//TotalBasicBullets - bulletToRecharge;
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(RechargeStatics().TotalBasicBulletsProperty, EGameplayModOp::Additive,  -bulletToRecharge));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(RechargeStatics().ChargerBasicBulletsProperty, EGameplayModOp::Additive, bulletToRecharge));

	}
	else if (bulletToRecharge>= TotalBasicBullets) {
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(RechargeStatics().TotalBasicBulletsProperty, EGameplayModOp::Additive, -TotalBasicBullets));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(RechargeStatics().ChargerBasicBulletsProperty, EGameplayModOp::Additive, TotalBasicBullets));

	}
	




}
