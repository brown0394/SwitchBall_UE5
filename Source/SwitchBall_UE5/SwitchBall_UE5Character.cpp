// Copyright Epic Games, Inc. All Rights Reserved.

#include "SwitchBall_UE5Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "SwitchBallBase.h"
#include "SwitchBallPlayerController.h"
#include "SwitchBallWidget.h"
#include "Components/PrimitiveComponent.h"


#define IMPULSELIMIT 100.0f
#define IMPULSEMULVAL 150.0f

//////////////////////////////////////////////////////////////////////////
// ASwitchBall_UE5Character

ASwitchBall_UE5Character::ASwitchBall_UE5Character()
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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(410.0, 0.0, 70.0));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	impulseToLaunch = 1.0f;
	shouldChargeIncrease = true;
}

void ASwitchBall_UE5Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	switchBall = Cast<ASwitchBallBase>(UGameplayStatics::GetActorOfClass(this, ASwitchBallBase::StaticClass()));
	switchBallPlayerController = Cast<ASwitchBallPlayerController>(UGameplayStatics::GetActorOfClass(this, ASwitchBallPlayerController::StaticClass()));
	this->SetActorTickEnabled(false);

}

void ASwitchBall_UE5Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (shouldChargeIncrease) {
		++impulseToLaunch;
	}
	else {
		--impulseToLaunch;
	}
	
	switchBallPlayerController->updateWidget(impulseToLaunch, IMPULSELIMIT);

	if (impulseToLaunch == IMPULSELIMIT ||impulseToLaunch == 0.0f) {
		shouldChargeIncrease = !shouldChargeIncrease;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASwitchBall_UE5Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASwitchBall_UE5Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASwitchBall_UE5Character::Look);

		EnhancedInputComponent->BindAction(SwitchAction, ETriggerEvent::Completed, this, &ASwitchBall_UE5Character::Switch);

		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ASwitchBall_UE5Character::ChargeImpulse);

		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &ASwitchBall_UE5Character::LaunchBall);
	}

}

void ASwitchBall_UE5Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
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

void ASwitchBall_UE5Character::Look(const FInputActionValue& Value)
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

void ASwitchBall_UE5Character::Switch()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Swtich"));
	
	if (!switchBall->GetLaunchAvailabilty()) {
		SetActorLocation(switchBall->GetActorLocation() + switchBall->GetActorUpVector() * 30);
		switchBall->AfterSwitch();
	}
}

void ASwitchBall_UE5Character::LaunchBall()
{
	if (switchBall->GetLaunchAvailabilty()) {
		this->SetActorTickEnabled(false);
		switchBallPlayerController->setWidgetVisiblilty(false);


		switchBall->EnableBall();
		switchBall->SetActorLocation(FollowCamera->K2_GetComponentLocation() + FollowCamera->GetForwardVector() * 20);
		switchBall->staticMesh->AddImpulse(FollowCamera->GetForwardVector() * impulseToLaunch * IMPULSEMULVAL);

		impulseToLaunch = 1.0f;
		shouldChargeIncrease = true;
	}
}

void ASwitchBall_UE5Character::ChargeImpulse() {
	if (switchBall->GetLaunchAvailabilty()) {
		switchBallPlayerController->setWidgetVisiblilty(true);
		this->SetActorTickEnabled(true);
	}
}