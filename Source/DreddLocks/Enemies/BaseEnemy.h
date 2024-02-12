// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIWaypointGeneral.h"
#include "BaseEnemy.generated.h"


class UHealtComponent;
UCLASS()
class DREDDLOCKS_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	/** COMPONENTS */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealtComponent* HealthComponent;

	/** ATTACK */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Enemy | Attack", meta = (DisplayName = "base Damage",
		ToolTip = "Daño base del enemigo"))
	float baseDamage = 10;
	/** SPAWN */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Enemy")
	FTransform initialTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	TArray<AAIWaypointGeneral*> TargetPoints;

private:
	bool isDead = false;
	bool isMoving = false;
	bool isAttacking = false;


public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void whenHpGoesTo0(DamageModes type);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Base Enemy", meta = (DisplayName = "Spawn"))
	virtual void spawn(FTransform spawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Base Enemy", meta = (DisplayName = "DeSpawn"))
	virtual void deSpawn();

};
