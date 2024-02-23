// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameplayEffect.h"
#include "../Enemies/BaseEnemy.h"
#include "BasicProjectil.generated.h"

UCLASS()
class DREDDLOCKS_API ABasicProjectil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectil();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
		float Range;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FGameplayEffectSpecHandle RechargeEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USphereComponent* SphereCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UStaticMeshComponent* ShootMesh;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
