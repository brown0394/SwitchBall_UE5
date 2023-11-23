// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftMovementComponent.h"

// Sets default values for this component's properties
ULiftMovementComponent::ULiftMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	xDistance = 0.0f;
	yDistance = 0.0f;
	zDistance = 0.0f;
	shouldReturn = false;
	wait = false;
	secPassed = 0.0f;
	timeToReachDest = 1.0f;
	alphaStep = 0.1f;
	secToWait = 0.0f;
	// ...
}


// Called when the game starts
void ULiftMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (owner != nullptr) {
		defaultLocation = owner->GetActorLocation();
		targetLocation = owner->ActorToWorld().TransformPositionNoScale(FVector(xDistance, yDistance, zDistance));
	}
	
	// ...
	alphaStep = 1 / timeToReachDest;
}

// Called every frame
void ULiftMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (timeToReachDest) {
		secPassed += DeltaTime;
		if (wait) {
			if (secToWait < 0) {
				secPassed = 0;
				wait = false;
				timeToReachDest = 0;
			}
			else if (secPassed > secToWait) {
				wait = false;
				secPassed = 0;
			}
		}
		else {
			if (shouldReturn) {
				FVector newLoc = FMath::Lerp(targetLocation, defaultLocation, secPassed * alphaStep);
				owner->SetActorLocation(newLoc);
				if (secPassed * alphaStep >= 1) {
					shouldReturn = false;
					secPassed = 0;
					wait = true;
				}
			}
			else {
				owner->SetActorLocation(FMath::Lerp(defaultLocation, targetLocation, secPassed * alphaStep));
				if (secPassed * alphaStep >= 1) {
					shouldReturn = true;
					secPassed = 0;
					wait = true;
				}
			}
		}
	}

	// ...
}

void ULiftMovementComponent::SetDestination(float x, float y, float z, float timeToReach, float sec) {
	timeToReachDest = timeToReach;
	secToWait = sec;
	alphaStep = 1 / timeToReachDest;
	defaultLocation = owner->GetActorLocation();
	targetLocation = owner->ActorToWorld().TransformPositionNoScale(FVector(x, y, z));
}