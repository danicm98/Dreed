// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimAbilityComponent.generated.h"

class ADreddLocksCharacter;


UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToogleAimEvent, bool, bActive);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DREDDLOCKS_API UAimAbilityComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UAimAbilityComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  /** Called for aim input */
  void Aim(const bool IsActive);

  /** Aim active */
  UFUNCTION()
  void BringCloserCameraArm();

  /** Aim inactive */
  UFUNCTION()
  void ReverseCameraArm();

private:
  ADreddLocksCharacter* DreddLock;

public:

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  bool bIsAiming = false;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  float AimingCameraArmLength = 75.f;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  float Range = 75.f;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  float NormalCameraArmLength = 100.f;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  float SmoothAimingRate = 0.02f;

  /* Handle to manage the timer */
  FTimerHandle AimTimerHandle;

  UPROPERTY(BlueprintAssignable, Category = "Aim", meta = (ToolTip = "Returns aiming state"))
  FToogleAimEvent ToogleAimEvent;

};
