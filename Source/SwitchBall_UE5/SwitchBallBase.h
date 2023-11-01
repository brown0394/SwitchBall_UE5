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
	UPROPERTY(EditAnywhere)
		class USphereComponent* collisionComponent;

	UPROPERTY(EditAnywhere)
		FVector defaultLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch")
		float ImpulseMulValue;

	virtual void EnableBall();
	virtual void DisableBall();
	void AfterSwitch();
	void FireInDirection(const FVector& FiringPosition, const FVector& ShootDirection, float impulseCharge);
	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USoundWave* HitSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
