// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//
#include "DreddLocks/GAS/GASGameplayAbility.h"
#include "DreddLocks/GAS/GASAbilitySystemComponent.h"
#include "DreddLocks/GAS/GASAttributeSet.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

#include "Logging/LogMacros.h"
#include "DreddLocksCharacter.generated.h"

class UGameplayEffect;
class USpringArmComponent;
class UCameraComponent;
class UGAS_BasicShoot;
class UInputMappingContext;
class UInputAction;
class UAimAbilityComponent;
class UShootingAbilityComponent;
struct FInputActionValue;
class UHealtComponent;
class UGASAttributeSet;

//DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType, meta = (DisplayName = "ShootMode"))
enum class ShootMode : uint8
{
    None UMETA(DispayName = "None"),
    Confirm UMETA(DispayName = "Confirm"),
    Cancel UMETA(DispayName = "Cancel"),
    Basic  UMETA(DisplayName = "Basic")
};


UENUM(BlueprintType, meta = (DisplayName = "States"))
enum class DreddState : uint8
{
  AIMING UMETA(DispayName = "AIMING"),
  NORMAL  UMETA(DisplayName = "NORMAL")
};

UDELEGATE(BlueprintAuthorityOnly)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDreddStateChangedEvent, DreddState, NewDreddStateType);



UCLASS(config = Game)
class ADreddLocksCharacter : public ACharacter, public IAbilitySystemInterface
{

  GENERATED_BODY()
public:

   

  /** Camera boom positioning the camera behind the character */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  USpringArmComponent* CameraBoom;

  /** Follow camera */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UCameraComponent* FollowCamera;

  /** Health Component*/
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UHealtComponent* HealthComponent;

  /** Shooting Ability Component*/
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UShootingAbilityComponent* ShootingAbilityComponent;

  /** Aim Ability Component*/
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UAimAbilityComponent* AimAbilityComponent;

  /** MappingContext */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputMappingContext* DefaultMappingContext;

  /** Jump Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* JumpAction;

  /** Move Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* MoveAction;

  /** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* LookAction;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIVision)
      UStaticMeshComponent* Weapon;


  /** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* ShootAction;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* RechargeAction;
  

  /** Aim Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* AimAction;

  /** Crouch Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* CrouchAction;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  bool bIsJumping = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  bool bIsCrouching = false;

  /**Actual State of Dredd */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  DreddState ActualDreddState = DreddState::NORMAL;

  /**Previous State of Dredd */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  DreddState PrevDreddState = DreddState::NORMAL;

  UPROPERTY(BlueprintAssignable, Category = "DreddState | Events", meta = (ToolTip = "Broadcast when the state is changed"))
      FDreddStateChangedEvent DreddStateChanged;



    
  //GAS

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
      class UGASAbilitySystemComponent* AbilitySystemComponent;
  
  virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override
  {
      return AbilitySystemComponent;
  }

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
      const class UGASAttributeSet* BasicAttributeSet;


  UFUNCTION(BlueprintPure, Category = "BaseCharacter")
      void GetHealthValues(float& Health , float& MaxHealth);

  UFUNCTION(BlueprintPure, Category = "BaseCharacter")
      void GetStaminaValues(float& Stamina, float& MaxStamina);

  UFUNCTION(BlueprintPure, Category = "BaseCharacter")
  void GetChargerBasicBulletsValues(float& ChargerBasicBullets, float& MaxChargerBasicBullets);

  UFUNCTION(BlueprintPure, Category = "BaseCharacter")
  void GetTotalBasicBulletsValues(float& TotalBasicBullets, float& MaxTotalBasicBullets);

  void OnHealthCnhangeNative(const FOnAttributeChangeData& Data);
  void OnStaminaCnhangeNative(const FOnAttributeChangeData& Data);

  UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
      void OnHealthChanged(float OldValue, float NewValue);
  UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
      void OnStaminaChanged(float OldValue, float NewValue);

  UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
      //We use TSubclassOf to be able to use classes that come from UGameplayAbility
      void InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);

  
  UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
      TArray<TSubclassOf<class UGAS_BasicShoot>> CharacterAbilities;

  UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
      TSubclassOf<UGameplayAbility> BasicShootAbility;

  UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
      TSubclassOf<UGameplayAbility> RechargeAbility;


  virtual void AddCharacterAbilities();


  virtual int32 GetAbilityLevel(ShootMode AbilityID) const;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
      ShootMode ActualPlayerShootMode = ShootMode::Basic;

  
  

public:
  ADreddLocksCharacter();

protected:

  //virtual void PostInitializeComponents() override;
  /** Called for movement input */
  void Move(const FInputActionValue& Value);

  /** Called for looking input */
  void Look(const FInputActionValue& Value);

  /** Called for crouch input */
  void Crouch(const bool bValue);

  /** Called for shoot input */
  void Shoot(const bool bValue );

  void Recharge(const bool bValue);

  /** Called for crouch input */
  void JumpWithAnimation(const bool IsActive);

  // APawn interface
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  // To add mapping context
  virtual void BeginPlay();

  bool ASCInputBound = false;


  //Lista de habiilidades que habrá que inicializar y que heredad de UGASGameplayAbility

  /*
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
      TArray<TSubclassOf<UGASGameplayAbility>> PassiveGameplayEffects;
  */
  /*
  *  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
      TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;
  */

 


  //GAS

  





public:
  /** Returns CameraBoom subobject **/
  FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

  /** Returns FollowCamera subobject **/
  FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

  /**Triggers the capsule component of the character**/
  UFUNCTION(BlueprintCallable)
  void TriggerCapsuleComponent(const bool bActivate);

  /** Change the actual state of Dredd to a new one */
  void ChangeState(const DreddState NewDreddState);

  /** 
    - Go back to the previous state of dredd
    - Use it to exit an state
 */
  void ResetState();
  
};

