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
		FVector defaultLocation;

	void EnableBall();
	void DisableBall();
	void AfterSwitch();
	bool GetLaunchAvailabilty();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	bool canBeLaunched;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
