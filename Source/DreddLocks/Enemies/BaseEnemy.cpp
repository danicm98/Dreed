// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "../Components/HealtComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));


}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	initialTransform = GetActorTransform();

	
	
}

void ABaseEnemy::whenHpGoesTo0(DamageModes type)
{
	if (!isDead)
	{
		isDead = true;
		//efectos muerte

		deSpawn();
	}
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::spawn(FTransform spawnTransform)
{
	isDead = false;
	SetActorTransform(spawnTransform);


}

void ABaseEnemy::deSpawn()
{
	isDead = true;

	//de momento destruye pero podria hacerse una pull de enemigos
	this->Destroy();
}

