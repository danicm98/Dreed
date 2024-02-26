// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ShootMontageTask.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGDPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);


UCLASS()
class DREDDLOCKS_API UShootMontageTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UShootMontageTask(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;

		UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UShootMontageTask* PlayMontageAndWaitForEvent(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UAnimMontage* MontageToPlay,
			FGameplayTagContainer EventTags,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f);

		UPROPERTY(BlueprintAssignable)
			FGDPlayMontageAndWaitForEventDelegate EventReceived;
	
private:

	UPROPERTY()
		UAnimMontage* MontageToPlay;

	UPROPERTY()
		FGameplayTagContainer EventTags;

	UPROPERTY()
		float Rate;

	UPROPERTY()
		FName StartSection;

	UPROPERTY()
		float AnimRootMotionTranslationScale;

	UPROPERTY(BlueprintAssignable)
		FGDPlayMontageAndWaitForEventDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable)
		FGDPlayMontageAndWaitForEventDelegate OnCancelled;
	UPROPERTY(BlueprintAssignable)
		FGDPlayMontageAndWaitForEventDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
		FGDPlayMontageAndWaitForEventDelegate OnBlendOut;

	UPROPERTY()
		bool bStopWhenAbilityEnds;

	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void OnAbilityCancelled();

	bool StopPlayingMontage();


	FDelegateHandle EventHandle;
	FDelegateHandle CancelledHandle;
	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;

};
