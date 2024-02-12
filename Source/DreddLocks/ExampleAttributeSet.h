// Fill out your copyright notice in the Description page of Project Settings.
/*
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ExampleAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DREDDLOCKS_API UExampleAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:

	UExampleAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	

	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UExampleAttributeSet, Health);

	

	
	//Replication function
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);
};
*/