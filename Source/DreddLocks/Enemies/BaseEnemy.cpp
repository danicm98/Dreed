// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "../GAS/GAS_GameplayAbilityBase.h"
#include "../GAS/GAS_GameplayAbilityBase.h"
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


	AddCharacterAbilities();

	if (IsValid(AbilitySystemComponent))
	{
		BasicAttributeSet = AbilitySystemComponent->GetSet<UGAS_EnemyAttributeSet>();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BasicAttributeSet->GetEnemyHealthAttribute()).AddUObject(this, &ABaseEnemy::OnEnemyHealthCnhangeNative);


		
	}

	
	

		
	
	
}
void ABaseEnemy::AddCharacterAbilities() {

	for (TSubclassOf<UGAS_GameplayAbilityBase>& Ability : CharacterAbilities)
	{

		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));

	}
}



void ABaseEnemy::GetEnemyHealthValues(float& EnemyHealth, float& MaxHealth)
{
	EnemyHealth = BasicAttributeSet->GetEnemyHealth();
	MaxHealth = BasicAttributeSet->GetMaxHealth();

}

void ABaseEnemy::GetArmorValues(float& Armor, float& MaxArmor)
{
	Armor = BasicAttributeSet->GetArmor();
	MaxArmor = BasicAttributeSet->GetMaxArmor();
}

void ABaseEnemy::GetBasicDamageValues(float& BasicDamage)
{
	BasicDamage = BasicAttributeSet->GetBasicDamage();
}

void ABaseEnemy::OnEnemyHealthCnhangeNative(const FOnAttributeChangeData& Data)
{
	OnEnemyHealthChanged(Data.OldValue, Data.NewValue);
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
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

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

