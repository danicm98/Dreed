// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealtComponent.generated.h"


UENUM(BlueprintType, meta = (DisplayName = "Damage types"))
enum class DamageModes : uint8
{
	DAMAGE UMETA(DispayName = "DAMAGE"),
	HEALING  UMETA(DisplayName = "HEALING")
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthChangedEvent, float, oldHp, float, newHp, DamageModes, damageType);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZeroHealthEvent, DamageModes, DamageType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DREDDLOCKS_API UHealtComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//-- Variables de Vida --//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent | Health", meta = (DisplayName = "current health",
		ToolTip = "Vida actual de la entidad. Solo es editable a traves de funciones"))
	float currentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent | Health", meta = (DisplayName = "Initial health",
		ToolTip = "Vida inicial de la entidad.",
		ClampMin = 0, UIMin = 0))
	float initialHp = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent | Health", meta = (DisplayName = "Max health",
		ToolTip = "Vida maxima de la entidad. Su vida nunca podra ser mayor que este valor.",
		ClampMin = 0, UIMin = 0))
	float maxHp = 100;


	//-- Delegates de Vida --//
	UPROPERTY(BlueprintAssignable, Category = "HealthComponent | Events", meta = (ToolTip = "Ejecutado cuando la vida varía."))
	FHealthChangedEvent healthChangedEvent;

	UPROPERTY(BlueprintAssignable, Category = "HealthComponent | Events", meta = (ToolTip = "Ejecutado cuando la vida llega a cero."))
	FZeroHealthEvent zerohealthEvent;

public:	
	// Sets default values for this component's properties
	UHealtComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "HealthComponent", meta = (DisplayName = "Change health",
		ToolTip = "Cambia la vida actual de la entidad en un valor determinado por el parametro AmountHp."))
	// aumenta o reduce la vida dependiendo del DamageModes
	void changeHealth(float AmountHp, DamageModes type);
		
};
