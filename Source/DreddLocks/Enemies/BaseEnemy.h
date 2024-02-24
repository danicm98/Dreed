// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIWaypointGeneral.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "../Enemies/GAS_EnemyAttributeSet.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "BaseEnemy.generated.h"

class UGAS_EnemyAttributeSet;
class UHealtComponent;
UCLASS()
class DREDDLOCKS_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	/** COMPONENTS */


	/** ATTACK */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Enemy | Attack", meta = (DisplayName = "base Damage",
		ToolTip = "Daño base del enemigo"))
	float baseDamage = 10;
	/** SPAWN */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Enemy")
	FTransform initialTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	TArray<AAIWaypointGeneral*> TargetPoints;



	//GAS

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
		class UGASAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
		TArray<TSubclassOf<class UGAS_GameplayAbilityBase>> CharacterAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
		const class UGAS_EnemyAttributeSet* BasicAttributeSet;


	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetEnemyHealthValues(float& EnemyHealth, float& MaxHealth);


	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetArmorValues(float& Armor, float& MaxArmor);

	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
		void GetBasicDamageValues(float& BasicDamage);



	void OnEnemyHealthCnhangeNative(const FOnAttributeChangeData& Data);


	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
		void OnEnemyHealthChanged(float OldValue, float NewValue);





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

	void AddCharacterAbilities();

	

	

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
