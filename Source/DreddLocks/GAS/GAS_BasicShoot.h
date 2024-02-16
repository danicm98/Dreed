// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DreddLocks/Dredd/DreddLocksCharacter.h"
#include "Abilities/GameplayAbility.h"
#include "GAS_BasicShoot.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UGAS_BasicShoot : public UGameplayAbility
{

	GENERATED_BODY()

	public:

		UGAS_BasicShoot();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ShootMode AbilityInputID = ShootMode::None;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ShootMode AbilityID = ShootMode::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")

		bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};
