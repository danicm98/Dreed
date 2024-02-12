// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingAbilityComponent.h"
#include "Projectile.h"
#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"
#include "../Dredd/DreddLocksCharacter.h"
#include <Kismet/KismetSystemLibrary.h>
#include <NiagaraFunctionLibrary.h>
//#include "Projectile.h"


// Sets default values for this component's properties
UShootingAbilityComponent::UShootingAbilityComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...

  ShootEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ShootEffectComponent"));

}


// Called when the game starts
void UShootingAbilityComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  //DreddLock = Cast<ADreddLocksCharacter>(GetOwner());
}


// Called every frame
void UShootingAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UShootingAbilityComponent::StartShooting()
{
  //"pum pum pum pum" Westsidegunn
  if (ShootType == SHOOT_TYPE::GUN)
  {
    HitScanShoot();
    UE_LOG(LogTemp, Warning, TEXT("Gun Type"));
  }
  else {
    ProjectileShoot();
  }
}

void UShootingAbilityComponent::StopShooting()
{
  // please stop
}

void UShootingAbilityComponent::ProjectileShoot()
{
  TSubclassOf<AProjectile>* SubObj = Projectiles.Find(ShootType);

  if (SubObj)
  {
    AProjectile* Projectile = Projectiles.Find(ShootType)->GetDefaultObject();

    if (IsValid(Projectile))
    {
      Projectile->Shoot();
    }
  }
}

float UShootingAbilityComponent::GetRange()
{

  TSubclassOf<AProjectile>* SubObj = Projectiles.Find(ShootType);

  if (SubObj)
  {
    AProjectile* Projectile = Projectiles.Find(ShootType)->GetDefaultObject();

    if (IsValid(Projectile))
    {
      return Projectile->Range;
    }
  }
  float* Val = WeaponRanges.Find(ShootType);
  if (Val)
  {
    return *Val;

  }
  else {
    return -INFINITE_FLOAT;
  }
}

void UShootingAbilityComponent::HitScanShoot()
{
  FVector ForwardPlayer = GetOwner()->GetActorForwardVector();
  ForwardPlayer.Normalize();

  ShootImpactCheck(ForwardPlayer);

  UE_LOG(LogTemp, Warning, TEXT("HitShoot"));
}

void UShootingAbilityComponent::ShootImpactCheck(FVector ShootDirection)
{
  if (IsValid(GetOwner()))
  {
    FVector LineStart = WeaponMuzzle/*GetOwner()->GetMesh()->GetSocketLocation("Weapon_R_Muzzle")*/ /*+ 50.0f * ShootDirection*/;
    FVector LineEnd = LineStart + GetRange() * ShootDirection;
    FHitResult Hit;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(GetOwner());
    TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
    /*ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));*/


    bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
      GetWorld(),
      LineStart,
      LineEnd,
      ShotRadius,
      ObjectTypes,
      true,
      ActorsToIgnore,
      EDrawDebugTrace::Persistent,
      Hit,
      true,
      FLinearColor::Red,
      FLinearColor::Green,
      4.0f
    );


    //Try to hit an enemy
    if (bHit)
    {
      ShowShootEffectComponent(ShootDirection, LineStart, Hit);

      ShowHitEffect(ShootDirection, LineStart, Hit);

      ActionsTriggeredByHit(Hit);
    }
    else //If not, hit the world and draw the ray
    {

      FCollisionQueryParams TraceParams;

      DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Blue, true);

      if (GetWorld()->LineTraceSingleByChannel(Hit, LineStart, LineEnd, ECC_WorldStatic, TraceParams))
      {

        ShowShootEffectComponent(ShootDirection, LineStart, Hit);
        //UE_LOG(LogTemp, Warning, TEXT("Not Hit %s"), *LineEnd.ToString());

        ShowHitEffect(ShootDirection, LineStart, Hit);
      }
    }
  }
}


void UShootingAbilityComponent::ShowShootEffectComponent(FVector ShootDirection, FVector LineStart, FHitResult Hit)
{
  if (IsValid(ShootEffectComponent) && ShootEffectComponent->GetAsset())
  {
    UNiagaraComponent* ShootEffectComponentCopy = ShootEffectComponent;
    ShootEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetOwner(), ShootEffectComponent->GetAsset(), LineStart, GetOwner()->GetActorRotation());
    ShootEffectComponent->SetNiagaraVariableVec3(FString("HitVector"), LineStart);
    ShootEffectComponent = ShootEffectComponentCopy;
  }
}

void UShootingAbilityComponent::ShowHitEffect(FVector ShootDirection, FVector LineStart, FHitResult Hit) const
{
  if (HitEffect && IsValid(Hit.GetActor()))
  {
    //UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, Hit.GetActor()->GetActorLocation());
    UNiagaraComponent* HitEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint);
    HitEffectComponent->SetVariableFloat(FName("R"), Color.R);
    HitEffectComponent->SetVariableFloat(FName("G"), Color.G);
    HitEffectComponent->SetVariableFloat(FName("B"), Color.B);
    HitEffectComponent->SetVariableFloat(FName("A"), Color.A);
    HitEffectComponent->SetVariableLinearColor(FName("Color"), Color);
  }
}


void UShootingAbilityComponent::ActionsTriggeredByHit(const FHitResult& Hit) const
{
  // Not yet implemented
}
