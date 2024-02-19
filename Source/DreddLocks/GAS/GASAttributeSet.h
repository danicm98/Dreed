// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

/**
 * 
 */


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class DREDDLOCKS_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGASAttributeSet();



	//Health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes" )
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health);


	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxHealth);

	//Stamina

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxStamina);




	//Basic Weapon

	UPROPERTY(BlueprintReadOnly, Category = "Basic Weapon Attribute")
		FGameplayAttributeData ChargerBasicBullets;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, ChargerBasicBullets);

	UPROPERTY(BlueprintReadOnly, Category = "Basic Weapon Attribute")
		FGameplayAttributeData MaxChargerBasicBullets;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxChargerBasicBullets);

	UPROPERTY(BlueprintReadOnly, Category = "Basic Weapon Attribute")
		FGameplayAttributeData TotalBasicBullets;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, TotalBasicBullets);

	UPROPERTY(BlueprintReadOnly, Category = "Basic Weapon Attribute")
		FGameplayAttributeData MaxTotalBasicBullets;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxTotalBasicBullets);




	
	//Is in charge of comunicate us when a attribute change 

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	
};
