// Fill out your copyright notice in the Description page of Project Settings.


#include "../Dredd/BasicProjectil.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABasicProjectil::ABasicProjectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollsion"));
	RootComponent = SphereCollision;

	ShootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootMesh"));

	ShootMesh->SetupAttachment(RootComponent);
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasicProjectil::OnOverlapBegin);
}




void ABasicProjectil::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseEnemy* Actor = Cast<ABaseEnemy>(OtherActor);

	
if (IsValid(Actor)){
		
		this->Destroy();
		UGASAbilitySystemComponent* AbilityComponent = Actor->AbilitySystemComponent;

		//const FActiveGameplayEffectHandle CurrentSpecHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(DamageEffectSpecHandle.Data.Get());
		//FGameplayEffectActorInfo CurrentActorInfo(Actor, Instigator, AbilitySystemComponent, nullptr);
		//FGameplayEffectActivationInfo CurrentActivationInfo = AbilityComponent->MakeEffectContext();


		AbilityComponent->ApplyGameplayEffectToSelf(DamageEffect, 1.0f , AbilityComponent->MakeEffectContext());
		//AbilityComponent->ApplyGameplayEffectSpecToSelf(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, DamageEffectSpecHandle);
		
		
		//AbilityComponent->Applyga
	
	}

}

// Called when the game starts or when spawned
void ABasicProjectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



