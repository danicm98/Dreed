// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS_EnemyAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DREDDLOCKS_API UGAS_EnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGAS_EnemyAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData EnemyHealth;
	ATTRIBUTE_ACCESSORS(UGAS_EnemyAttributeSet, EnemyHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGAS_EnemyAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UGAS_EnemyAttributeSet, Armor);


	UPROPERTY(BlueprintReadOnly, Category = "BasicDamage")
		FGameplayAttributeData BasicDamage;
	ATTRIBUTE_ACCESSORS(UGAS_EnemyAttributeSet, BasicDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UGAS_EnemyAttributeSet, MaxArmor);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;




	
};
