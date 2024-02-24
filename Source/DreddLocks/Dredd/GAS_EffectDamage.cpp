// Fill out your copyright notice in the Description page of Project Settings.


#include "../Dredd/GAS_EffectDamage.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "../Enemies/GAS_EnemyAttributeSet.h"

struct GDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnemyHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BasicDamage);


	GDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_EnemyAttributeSet, BasicDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_EnemyAttributeSet, EnemyHealth, Target, false);


	}


};

static const GDDamageStatics& DamageStatics()
{
	static GDDamageStatics DStatics;
	return DStatics;
}


UGAS_EffectDamage::UGAS_EffectDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().BasicDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().EnemyHealthDef);

}

void UGAS_EffectDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Health = 0.f;
	float Damage = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BasicDamageDef, EvaluationParameters, Damage);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().EnemyHealthDef, EvaluationParameters, Health);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().EnemyHealthProperty, EGameplayModOp::Additive, -Damage));
	
}
