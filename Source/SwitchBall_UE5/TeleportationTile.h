// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportationTile.generated.h"

UCLASS()
class SWITCHBALL_UE5_API ATeleportationTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeleportationTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		UStaticMeshComponent* staticMesh;

	FVector playerStartLocation;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* materialInstance;

	UFUNCTION()
		void NotifyHit(
			UPrimitiveComponent* MyComp,
			AActor* Other,
			UPrimitiveComponent* OtherComp,
			bool bSelfMoved,
			FVector HitLocation,
			FVector HitNormal,
			FVector NormalImpulse,
			const FHitResult& Hit
		);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
