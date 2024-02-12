// Fill out your copyright notice in the Description page of Project Settings.


#include "HealtComponent.h"

// Sets default values for this component's properties
UHealtComponent::UHealtComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealtComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	currentHp = initialHp;
}


// Called every frame
void UHealtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealtComponent::changeHealth(float AmountHp, DamageModes type)
{

	float oldHp = currentHp;
	if (type == DamageModes::DAMAGE)
	{
		//recibe daño
		currentHp = FMath::Clamp<float>((currentHp - AmountHp), 0.0f, maxHp);
	}
	else
	{
		//se cura
		currentHp = FMath::Clamp<float>((currentHp + AmountHp), 0.0f, maxHp);
	}

	if (currentHp == 0)
	{
		zerohealthEvent.Broadcast(type);
	}

	healthChangedEvent.Broadcast(oldHp, currentHp, type);

#if WITH_EDITOR 
	UE_LOG(LogTemp, Warning, TEXT("Entidad recibe cambio de vida, ahora tiene %f vida"), currentHp);
#endif
}

