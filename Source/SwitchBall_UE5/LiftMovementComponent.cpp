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
	LerpAlpha = 0.1f;
	shouldReturn = false;
	// ...
}


// Called when the game starts
void ULiftMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (owner != nullptr) {
		defaultLocation = owner->GetActorLocation();
	}
	targetLocation = owner->ActorToWorld().TransformPositionNoScale(FVector(xDistance, yDistance, zDistance));
	// ...
	
}


// Called every frame
void ULiftMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (shouldReturn) {
		owner->SetActorLocation(FMath::Lerp(owner->GetActorLocation(), defaultLocation, LerpAlpha));
		if (FVector::Distance(owner->GetActorLocation(), defaultLocation) < 1.0f) {
			shouldReturn = false;
		}
	}
	else {
		owner->SetActorLocation(FMath::Lerp(owner->GetActorLocation(), targetLocation, LerpAlpha));
		if (FVector::Distance(owner->GetActorLocation(), targetLocation) < 1.0f) {
			shouldReturn = true;
		}
	}
	
	// ...
}

