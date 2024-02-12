// Fill out your copyright notice in the Description page of Project Settings.


#include "AimAbilityComponent.h"
#include "../Dredd/DreddLocksCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 


// Sets default values for this component's properties
UAimAbilityComponent::UAimAbilityComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...

}


// Called when the game starts
void UAimAbilityComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  DreddLock = Cast<ADreddLocksCharacter>(GetOwner());
  NormalCameraArmLength = DreddLock->GetCameraBoom()->TargetArmLength;
}


// Called every frame
void UAimAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}


void UAimAbilityComponent::Aim(const bool IsActive)
{
  bIsAiming = IsActive;
  if (bIsAiming)
  {
    DreddLock->ChangeState(DreddState::AIMING);
    DreddLock->GetCharacterMovement()->bUseControllerDesiredRotation = true;
    ToogleAimEvent.Broadcast(true);
    GetWorld()->GetTimerManager().SetTimer(
      AimTimerHandle,
      this,
      &UAimAbilityComponent::BringCloserCameraArm,
      SmoothAimingRate,
      true);
  }
  else
  {
    DreddLock->ResetState();
    DreddLock->GetCharacterMovement()->bUseControllerDesiredRotation = false;
    ToogleAimEvent.Broadcast(false);
    GetWorld()->GetTimerManager().SetTimer(
      AimTimerHandle,
      this,
      &UAimAbilityComponent::ReverseCameraArm,
      SmoothAimingRate,
      true);
  }

}

void UAimAbilityComponent::BringCloserCameraArm()
{
  if (DreddLock->GetCameraBoom()->TargetArmLength > AimingCameraArmLength)
  {
    DreddLock->GetCameraBoom()->TargetArmLength -= 0.5f;
  }
  else
  {
    GetWorld()->GetTimerManager().ClearTimer(AimTimerHandle);
  }

}

void UAimAbilityComponent::ReverseCameraArm()
{
  if (DreddLock->GetCameraBoom()->TargetArmLength < NormalCameraArmLength)
  {
    DreddLock->GetCameraBoom()->TargetArmLength += 0.5f;
  }
  else
  {
    GetWorld()->GetTimerManager().ClearTimer(AimTimerHandle);
  }
}