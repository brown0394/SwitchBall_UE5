// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PusherCharacter.generated.h"

UCLASS()
class SWITCHBALL_UE5_API APusherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APusherCharacter();
	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
		TObjectPtr<class UBehaviorTree> PusherBehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Sphere")
		TObjectPtr<class USphereComponent> OverlapSphere;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
		TObjectPtr<AActor> TrashBin;

	UPROPERTY(EditAnywhere, Category = "Distance")
		float DistanceWithBall;

	UPROPERTY(EditAnywhere, Category = "Distance")
		float DistanceWithPlayer;

	bool isBallCloseEnough();
	TObjectPtr<class ASwitchBall_UE5Character> getPlayerOverlapped();
	TObjectPtr<class ASwitchBallBase> getBallOverlapped();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	TObjectPtr<class ASwitchBallBase> ballOverlapped;
	TObjectPtr<class ASwitchBall_UE5Character> characterOverlapped;
	FVector DefaultLocation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FVector GetDefaultLocation();
};
