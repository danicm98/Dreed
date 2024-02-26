// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GAS/GAS_BasicShoot.h"
#include "../Dredd/BasicProjectil.h"
#include "MyGAS_BasicShoot.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UMyGAS_BasicShoot : public UGAS_BasicShoot
{
	GENERATED_BODY()

public:
	
	UMyGAS_BasicShoot();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Range = 1000.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Damage = 12.0f;



	//Este metodo es necesario para activar la tag pero no lo llamamos para activarla sino que llamamos a  APAHeroCharacter::ActivateAbilitiesWithTags()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const;

	void ThrowAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<ABasicProjectil> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect> DamageGameplayEffect;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UAnimMontage* FireHipMontage;

	
};
