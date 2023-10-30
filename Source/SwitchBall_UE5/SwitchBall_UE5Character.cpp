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
#include "StickyBall.h"
#include "EyeBall.h"
#include "FPSProjectile.h"

#define IMPULSELIMIT 100.0f


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
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));//(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // xCamera does not rotate relative to armx  Rotate the arm based on the controller
	FollowCamera->SetRelativeLocation(FVector(20.0f, 0.0f, BaseEyeHeight));


	bUseControllerRotationYaw = true;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	impulseToLaunch = 1.0f;
	shouldChargeIncrease = true;
	currentBall = ballType::SWITCHBALL;
	canLaunchBall = true;
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
	switchBalls.Add(Cast<ASwitchBallBase>(UGameplayStatics::GetActorOfClass(this, ASwitchBallBase::StaticClass())));
	switchBalls.Add(Cast<ASwitchBallBase>(UGameplayStatics::GetActorOfClass(this, AStickyBall::StaticClass())));
	switchBalls.Add(Cast<ASwitchBallBase>(UGameplayStatics::GetActorOfClass(this, AEyeBall::StaticClass())));
	switchBallPlayerController = Cast<ASwitchBallPlayerController>(UGameplayStatics::GetActorOfClass(this, ASwitchBallPlayerController::StaticClass()));
	this->SetActorTickEnabled(false);

}

void ASwitchBall_UE5Character::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(timeHandle);
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

		EnhancedInputComponent->BindAction(ChangeToSwitchBallAction, ETriggerEvent::Completed, this, &ASwitchBall_UE5Character::ChangeToSwitchBall);

		EnhancedInputComponent->BindAction(ChangeToStickyBallAction, ETriggerEvent::Completed, this, &ASwitchBall_UE5Character::ChangeToStickyBall);

		EnhancedInputComponent->BindAction(ChangeToEyeBallAction, ETriggerEvent::Completed, this, &ASwitchBall_UE5Character::ChangeToEyeBall);
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
	
	if (!canLaunchBall) {
		if (currentBall != 2) {
			SetActorLocation(switchBalls[currentBall]->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f));
		}
		switchBalls[currentBall]->AfterSwitch();
		canLaunchBall = true;
	}
}

void ASwitchBall_UE5Character::LaunchBall()
{
	if (canLaunchBall) {
		this->SetActorTickEnabled(false);
		switchBallPlayerController->setProgressBarVisiblilty(false);

		//switchBalls[currentBall]->staticMesh->AddImpulse(FollowCamera->GetForwardVector() * impulseToLaunch * IMPULSEMULVAL);
		switchBalls[currentBall]->FireInDirection(FollowCamera->K2_GetComponentLocation() + FollowCamera->GetForwardVector() * 100, FollowCamera->GetForwardVector(), impulseToLaunch);
		impulseToLaunch = 1.0f;
		shouldChargeIncrease = true;
		canLaunchBall = false;
	}
}

void ASwitchBall_UE5Character::ChargeImpulse() {
	if (canLaunchBall) {
		switchBallPlayerController->setProgressBarVisiblilty(true);
		this->SetActorTickEnabled(true);
	}
}

void ASwitchBall_UE5Character::ChangeToSwitchBall() {
	if (canLaunchBall) {
		FTimerManager* timerManager = &GetWorld()->GetTimerManager();
		CheckTimerAndSetTextVisibility(timerManager);
		currentBall = ballType::SWITCHBALL;
		timerManager->SetTimer(timeHandle, this, &ASwitchBall_UE5Character::HideSwitchBallText, 2, false);
		switchBallPlayerController->setBallTextVisiblilty(true, ballType::SWITCHBALL);
	}
}

void ASwitchBall_UE5Character::ChangeToStickyBall() {
	if (canLaunchBall) {
		FTimerManager* timerManager = &GetWorld()->GetTimerManager();
		CheckTimerAndSetTextVisibility(timerManager);
		currentBall = ballType::STICKYBALL;
		timerManager->SetTimer(timeHandle, this, &ASwitchBall_UE5Character::HideStickyBallText, 2, false);
		switchBallPlayerController->setBallTextVisiblilty(true, ballType::STICKYBALL);
	}
}

void ASwitchBall_UE5Character::ChangeToEyeBall() {
	if (canLaunchBall) {
		FTimerManager* timerManager = &GetWorld()->GetTimerManager();
		CheckTimerAndSetTextVisibility(timerManager);
		currentBall = ballType::EYEBALL;
		timerManager->SetTimer(timeHandle, this, &ASwitchBall_UE5Character::HideEyeBallText, 2, false);
		switchBallPlayerController->setBallTextVisiblilty(true, ballType::EYEBALL);
	}
}

ASwitchBallBase* ASwitchBall_UE5Character::getBallLaunched() {
	if (canLaunchBall) return nullptr;
	return switchBalls[currentBall];
}

void ASwitchBall_UE5Character::HideSwitchBallText() {
	switchBallPlayerController->setBallTextVisiblilty(false, ballType::SWITCHBALL);
}

void ASwitchBall_UE5Character::HideStickyBallText() {
	switchBallPlayerController->setBallTextVisiblilty(false, ballType::STICKYBALL);
}

void ASwitchBall_UE5Character::HideEyeBallText() {
	switchBallPlayerController->setBallTextVisiblilty(false, ballType::EYEBALL);
}

void ASwitchBall_UE5Character::CheckTimerAndSetTextVisibility(FTimerManager* timerManager) {
	if (timerManager->IsTimerActive(timeHandle)) {
		timerManager->ClearTimer(timeHandle);
		switchBallPlayerController->setBallTextVisiblilty(false, static_cast<ballType>(currentBall));
	}
}