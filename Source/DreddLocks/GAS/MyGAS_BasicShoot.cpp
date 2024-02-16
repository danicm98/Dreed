// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/MyGAS_BasicShoot.h"
#include "GameplayTagContainer.h"
#include "../Dredd/DreddLocksCharacter.h"
#include "../Dredd/BasicProjectil.h"
#include "Kismet/KismetMathLibrary.h"

UMyGAS_BasicShoot::UMyGAS_BasicShoot()
{
	AbilityInputID = ShootMode::Basic;
	//Se hace en todos las habilidades , y es para que cada actor tenga su instancia de habilidad propia
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	//creramos una tag a la habilidad
	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Basic"));

	//Añadimos la tag
	AbilityTags.AddTag(Ability1Tag);

	//Activamos la tag
	ActivationOwnedTags.AddTag(Ability1Tag);

	//Tags que bloquean nuestra habilidad
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));


}

void UMyGAS_BasicShoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//Esto nos indica si algo ha fallado
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		//Si algo falla finaliza la habilidad
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		
	}

	ThrowAbility();

	//Le asignamos un montaje que podemos reproducir cuando se realice la habilidad
	//UAnimMontage* MontageToPlay = FireHipMontage;

	/* Esto es si esta apuntando que tenga otra animacion no nos interesa por ahora
	if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.AimDownSights"))) &&
		!GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.AimDownSights.Removal"))))
	{
		MontageToPlay = FireIronsightsMontage;
	}
	*/

	//Aqui se ejecuta la animacion en una task ,`por ahora no nos interesa
	//UGDAT_PlayMontageAndWaitForEvent* Task = UGDAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, NAME_None, false, 1.0f);
	
	/* 
	Task->OnBlendOut.AddDynamic(this, &UGDGA_FireGun::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &UGDGA_FireGun::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &UGDGA_FireGun::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UGDGA_FireGun::OnCancelled);
	Task->EventReceived.AddDynamic(this, &UGDGA_FireGun::EventReceived);
	*/

	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	//Task->ReadyForActivation();


}
/*
bool UMyGAS_BasicShoot::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	else {
		return true;
	}

}
*/

void UMyGAS_BasicShoot::ThrowAbility() {

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Throw Ability");
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	

	
	ADreddLocksCharacter* Hero = Cast<ADreddLocksCharacter>(GetAvatarActorFromActorInfo());
	if (!Hero)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	FVector ForwardPlayer = Hero->GetActorForwardVector();
	FVector Start = Hero->Weapon->GetComponentLocation();
	FVector End = Start + Range * ForwardPlayer.Normalize();;
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	FTransform MuzzleTransform = Hero->Weapon->GetComponentTransform();
	MuzzleTransform.SetRotation(Rotation.Quaternion());

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	

	ABasicProjectil* Projectile = GetWorld()->SpawnActorDeferred<ABasicProjectil>(ProjectileClass, MuzzleTransform, GetOwningActorFromActorInfo(), Hero, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	/*
	* 	
	Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
	Projectile->Range = Range;
	Projectile->FinishSpawning(MuzzleTransform);
	*/
	Projectile->FinishSpawning(MuzzleTransform);

}




