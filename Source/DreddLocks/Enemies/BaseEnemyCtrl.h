// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemy.h"
#include "BaseEnemyCtrl.generated.h"

/**
 * 
 */
UCLASS()
class DREDDLOCKS_API ABaseEnemyCtrl : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnemy | Controller", meta = (DisplayName = "EnemyBasePawn"))
	ABaseEnemy* enemyPawn;

public:
	virtual void BeginPlay() override;


	//Devuelve un booleano para poder indicar si el ataque se ha realizado o si por alguna razon, se ha tenido que cancelar.
	//esta funcion seria la generica de los enemigos para atacar porque minimo van a tener un ataque
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy | Controller", meta = (DisplayName = "DoBasicAttack"))
	virtual bool DoBasicAttack(FVector targetPosition);

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy | Controller", meta = (DisplayName = "MoveToPosition"))
	virtual EPathFollowingRequestResult::Type moveToPosition(FVector targetPosition);

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy | Controller", meta = (DisplayName = "Rotate towards target"))
	void rotatePawnTowardsTargetXY(FVector targetPosition);

	UFUNCTION(BlueprintCallable, Category = "Order")
	void UpdateNextTargetPoint();
};
