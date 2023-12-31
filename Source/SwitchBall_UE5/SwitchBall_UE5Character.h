// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SwitchBall_UE5Character.generated.h"


UCLASS(config=Game)
class ASwitchBall_UE5Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UCameraComponent> FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> SwitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ChangeToSwitchBallAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ChangeToStickyBallAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ChangeToEyeBallAction;

public:
	ASwitchBall_UE5Character();
	TObjectPtr<class ASwitchBallBase> getBallLaunched();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	void Switch();

	void ChargeImpulse();

	void LaunchBall();

	void ChangeToSwitchBall();

	void ChangeToStickyBall();

	void ChangeToEyeBall();

	void HideSwitchBallText();

	void HideStickyBallText();

	void HideEyeBallText();

	void CheckTimerAndSetTextVisibility(FTimerManager* timerManager);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY()
	TObjectPtr<class ASwitchBallPlayerController> switchBallPlayerController;
	float impulseToLaunch;
	bool shouldChargeIncrease;

	UPROPERTY()
	TArray<TObjectPtr<class ASwitchBallBase>> switchBalls;
	int currentBall;
	bool canLaunchBall;
	UPROPERTY()
	FTimerHandle timeHandle;

	UPROPERTY()
		FTimerHandle SwitchTimeHandle;

	UPROPERTY()
		TObjectPtr<USoundWave> TeleportationSound;
	UPROPERTY()
		TObjectPtr<USoundWave> SelectionSound;

	UPROPERTY()
		TObjectPtr<USoundWave> LaunchSound;

	void playTeleportSound();
};

