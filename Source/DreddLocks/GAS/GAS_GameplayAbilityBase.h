// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DreddLocks/Dredd/DreddLocksCharacter.h"
#include "GAS_GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API UGAS_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()


public:
	UGAS_GameplayAbilityBase();


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ShootMode AbilityInputID = ShootMode::None;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ShootMode AbilityID = ShootMode::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")

		bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	
};
