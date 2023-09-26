// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchBallBase.generated.h"

UCLASS()
class SWITCHBALL_UE5_API ASwitchBallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitchBallBase();
	UPROPERTY()
		UStaticMeshComponent* staticMesh;
	UPROPERTY()
		class USphereComponent* collisionComponent;
	UPROPERTY()
		class UProjectileMovementComponent* projectileMovementComponent;
	UPROPERTY(EditAnywhere)
		FVector defaultLocation;

	virtual void EnableBall();
	virtual void DisableBall();
	void AfterSwitch();
	void FireInDirection(const FVector& FiringPosition, const FVector& ShootDirection, float impulseCharge);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
