// Fill out your copyright notice in the Description page of Project Settings.
/*

#include "ExampleAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "Net/UnrealNetwork.h"

UExampleAttributeSet::UExampleAttributeSet() : Health(100.0f)
{
}

void UExampleAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UExampleAttributeSet, Health);
	//DOREPLIFETIME_CONDITION_NOTIFY(UExampleAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

//Se llama cuando se actualiza el valor
void UExampleAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UExampleAttributeSet , Health , OldValue);
}

*/
