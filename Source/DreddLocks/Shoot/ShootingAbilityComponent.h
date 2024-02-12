// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootingAbilityComponent.generated.h"

UENUM(BlueprintType)
enum SHOOT_TYPE : uint8
{
  GUN,
  FIREBALL,
  STUN
};

#define INFINITE_FLOAT (float)0x7F800000

class ADreddLocksCharacter;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DREDDLOCKS_API UShootingAbilityComponent : public UActorComponent
{
  GENERATED_BODY()

public:

  UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  TEnumAsByte < SHOOT_TYPE> ShootType = SHOOT_TYPE::GUN;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  TMap<TEnumAsByte<SHOOT_TYPE>, TSubclassOf<class AProjectile>> Projectiles;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  TMap<TEnumAsByte<SHOOT_TYPE>, float> WeaponRanges;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Shot")
  float ShotRadius = 8.0f;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Shot")
  UNiagaraComponent* ShootEffectComponent;

  //Hit effect spawn when Shoot hit shomething
  UPROPERTY(EditAnywhere, category = "Shot")
  UNiagaraSystem* HitEffect;

  UPROPERTY(EditAnywhere, category = "Shot")
  FLinearColor Color;

  UPROPERTY(EditAnywhere, category = "Shot")
  FVector WeaponMuzzle;

public:
  // Sets default values for this component's properties
  UShootingAbilityComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  // Start To Shoot
  void StartShooting();

  void ProjectileShoot();

  float GetRange();

  void HitScanShoot();

  //Stop Shooting
  void StopShooting();

  void ShootImpactCheck(FVector ShootDirection);

  void ShowShootEffectComponent(FVector ShootDirection, FVector LineStart, FHitResult Hit);

  void ShowHitEffect(FVector ShootDirection, FVector LineStart, FHitResult Hit) const;

  void ActionsTriggeredByHit(const FHitResult& Hit) const;
};
