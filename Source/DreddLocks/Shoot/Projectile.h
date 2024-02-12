// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "Projectile.generated.h"

UCLASS()
class DREDDLOCKS_API AProjectile : public AActor
{
  GENERATED_BODY()

public:

  UPROPERTY(EditAnywhere)
  USphereComponent* SphereComponent;

public:
  // Sets default values for this actor's properties
  AProjectile();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  void Shoot() {};

  float Range = 75.f;


};
