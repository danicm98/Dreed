// Copyright Epic Games, Inc. All Rights Reserved.

#include "DreddLocksCharacter.h"
#include "DreddLocksCharacter.h"
#include "Engine/LocalPlayer.h"

#include "DreddLocks/GAS/GAS_BasicShoot.h"
#include "DreddLocks/GAS/Prueba.h"
#include "DreddLocks/GAS/GASGameplayAbility.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "DreddLocks/GAS/GASAttributeSet.h"
//#include "../DreddLocks/MyAbilitySystemComponent"

#include "Components/ArrowComponent.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "../Shoot/ShootingAbilityComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <DreddLocks/Shoot/AimAbilityComponent.h>
#include "../Components/HealtComponent.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);


//////////////////////////////////////////////////////////////////////////
// ADreddLocksCharacter






ADreddLocksCharacter::ADreddLocksCharacter()
{




  // Set size for collision capsule
  GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

  // Don't rotate when the controller rotates. Let that just affect the camera.
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;

  // Configure character movement
  GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
  GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

  // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
  // instead of recompiling to adjust them
  GetCharacterMovement()->JumpZVelocity = 700.f;
  GetCharacterMovement()->AirControl = 0.35f;
  GetCharacterMovement()->MaxWalkSpeed = 500.f;
  GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
  GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
  GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

  // Create a camera boom (pulls in towards the player if there is a collision)
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);
  //CameraBoom->TargetArmLength = NormalCameraArmLength; // The camera follows at this distance behind the character	
  CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

  // Create a follow camera
  FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
  FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
  FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

  HealthComponent = CreateDefaultSubobject<UHealtComponent>(TEXT("HealthComponent"));
  AddOwnedComponent(RootComponent);

  // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
  // are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
  Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
  //FollowCamera->SetupAttachment(GetMesh());
  Weapon->SetupAttachment(GetMesh());


  //Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Weapon_R"));


  ShootingAbilityComponent = CreateDefaultSubobject<UShootingAbilityComponent>(TEXT("ShootingAbility"));
  AimAbilityComponent = CreateDefaultSubobject<UAimAbilityComponent>(TEXT("AimAbility"));

  //GAS

  AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}




void ADreddLocksCharacter::BeginPlay()
{
  // Call the base class  
  Super::BeginPlay();



  //GAS
  AddCharacterAbilities();

  if (IsValid(AbilitySystemComponent))
  {
      BasicAttributeSet = AbilitySystemComponent->GetSet<UGASAttributeSet>();

      AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BasicAttributeSet->GetHealthAttribute()).AddUObject(this, &ADreddLocksCharacter::OnHealthCnhangeNative);
      AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BasicAttributeSet->GetStaminaAttribute()).AddUObject(this, &ADreddLocksCharacter::OnStaminaCnhangeNative);
  }


  //Add Input Mapping Context
  if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
  }
}

/*
* void ADreddLocksCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (Weapon && GetMesh())
    {
        Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Weapon_R"));
    }
}
*/




//////////////////////////////////////////////////////////////////////////
// Input

void ADreddLocksCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  // Set up action bindings
  if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

    // Jumping
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADreddLocksCharacter::JumpWithAnimation, true);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADreddLocksCharacter::JumpWithAnimation, false);

    // Moving
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADreddLocksCharacter::Move);

    // Looking
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADreddLocksCharacter::Look);

    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ADreddLocksCharacter::Crouch, true);
    EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ADreddLocksCharacter::Crouch, false);

    EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ADreddLocksCharacter::Shoot, true);
    EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ADreddLocksCharacter::Shoot, false);

    EnhancedInputComponent->BindAction(RechargeAction, ETriggerEvent::Started, this, &ADreddLocksCharacter::Recharge, true);
    EnhancedInputComponent->BindAction(RechargeAction, ETriggerEvent::Completed, this, &ADreddLocksCharacter::Recharge, false);

    EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, AimAbilityComponent, &UAimAbilityComponent::Aim, true);
    EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, AimAbilityComponent, &UAimAbilityComponent::Aim, false);
  }
  else
  {
    //UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
  }
}


void ADreddLocksCharacter::Move(const FInputActionValue& Value)
{
  // input is a Vector2D
  FVector2D MovementVector = Value.Get<FVector2D>();

  if (Controller != nullptr /*&& !bIsJumping*/)
  {
    // find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get forward vector
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    // get right vector 
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // add movement 
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
  }
}

void ADreddLocksCharacter::Look(const FInputActionValue& Value)
{
  // input is a Vector2D
  FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (Controller != nullptr)
  {

    // add yaw and pitch input to controller
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
  }
}

void ADreddLocksCharacter::Crouch(const bool bValue)
{
  if (bValue)
  {
    bIsCrouching = true;
    UE_LOG(LogTemp, Warning, TEXT("Crouch: true"));

  }
  else {
    bIsCrouching = false;
    UE_LOG(LogTemp, Warning, TEXT("Crouch: false"));
  }
}

void ADreddLocksCharacter::Shoot(const bool bValue )
{
    //Para que se llame solo cuando se pulse
    if (bValue && ActualPlayerShootMode == ShootMode::Basic)
    {
    AbilitySystemComponent->TryActivateAbilityByClass(BasicShootAbility);
    }
}

void ADreddLocksCharacter::Recharge(const bool bValue)
{
    if (bValue) {
        AbilitySystemComponent->TryActivateAbilityByClass(RechargeAbility);
    }

}



void ADreddLocksCharacter::TriggerCapsuleComponent(bool bActivate)
{
  if (bActivate)
  {
    GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    //StopJumping();
  }
  else
  {
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

    //Jump();
    GetCapsuleComponent()->SetCapsuleHalfHeight(10.f);
  }
}

void ADreddLocksCharacter::JumpWithAnimation(bool IsActive)
{
  bIsJumping = IsActive;
  UE_LOG(LogTemp, Warning, TEXT("Jump!"));
  //Jump();
}

void ADreddLocksCharacter::ChangeState(const DreddState NewDreddState)
{
  this->PrevDreddState = ActualDreddState;

  this->ActualDreddState = NewDreddState;

  DreddStateChanged.Broadcast(ActualDreddState);
}

void ADreddLocksCharacter::ResetState()
{
  ChangeState(PrevDreddState);
}



//GAS

void ADreddLocksCharacter::GetHealthValues(float& Health, float& MaxHealth)
{
    Health = BasicAttributeSet->GetHealth();
    MaxHealth = BasicAttributeSet->GetMaxHealth();

}

void ADreddLocksCharacter::GetStaminaValues(float& Stamina, float& MaxStamina)
{

    Stamina = BasicAttributeSet->GetStamina();
    MaxStamina = BasicAttributeSet->GetMaxStamina();
}

void ADreddLocksCharacter::GetChargerBasicBulletsValues(float& ChargerBasicBullets, float& MaxChargerBasicBullets)
{

    ChargerBasicBullets = BasicAttributeSet->GetChargerBasicBullets();
    MaxChargerBasicBullets = BasicAttributeSet->GetMaxChargerBasicBullets();
}

void ADreddLocksCharacter::GetTotalBasicBulletsValues(float& TotalBasicBullets, float& MaxTotalBasicBullets)
{

    TotalBasicBullets = BasicAttributeSet->GetTotalBasicBullets();
    MaxTotalBasicBullets = BasicAttributeSet->GetMaxTotalBasicBullets();
}


void ADreddLocksCharacter::OnHealthCnhangeNative(const FOnAttributeChangeData& Data)
{
    OnHealthChanged(Data.OldValue, Data.NewValue);
}

void ADreddLocksCharacter::OnStaminaCnhangeNative(const FOnAttributeChangeData& Data)
{
    OnStaminaChanged(Data.OldValue, Data.NewValue);
}

void ADreddLocksCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel )
{

    if (AbilitySystemComponent) {

        if (HasAuthority() && AbilityToGet) {

            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
        }
        AbilitySystemComponent->InitAbilityActorInfo(this, this);

    }

    
}

void ADreddLocksCharacter::AddCharacterAbilities()
{

    if (!IsValid(AbilitySystemComponent) || AbilitySystemComponent->bCharacterAbilitiesGiven) {
        return;
    }

    for (TSubclassOf<UGAS_BasicShoot>& StartupAbility : CharacterAbilities)
    {
     
        AbilitySystemComponent->GiveAbility(
            FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
    }

    AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

int32 ADreddLocksCharacter::GetAbilityLevel(ShootMode AbilityID) const
{
    return 1;
}



