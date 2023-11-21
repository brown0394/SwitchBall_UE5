// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerMoveTriggerBox.h"
#include "SwitchBall_UE5Character.h"
#include "LiftMovementComponent.h"

ATimerMoveTriggerBox::ATimerMoveTriggerBox() {
	target = nullptr;
	xDistance = 0.0f;
	yDistance = 0.0f;
	zDistance = 0.0f;
	secToWait = 0.0f;
	timeToReachDest = 1.0f;
}

void ATimerMoveTriggerBox::BeginPlay() {
	Super::BeginPlay();
	TSet<UActorComponent*> arr = target->GetComponents();
	for (UActorComponent* elem : arr) {
		if (targetMovementComp = Cast<ULiftMovementComponent>(elem)) {
			break;
		}
	}
}

void ATimerMoveTriggerBox::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(timeHandle);
}

void ATimerMoveTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor) {
	TObjectPtr<ASwitchBall_UE5Character> character = Cast<ASwitchBall_UE5Character>(OtherActor);
	if (character) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("timer triggered"));
		GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &ATimerMoveTriggerBox::MoveTarget, 10, false);
	}
}

void ATimerMoveTriggerBox::NotifyActorEndOverlap(AActor* OtherActor) {
	TObjectPtr<ASwitchBall_UE5Character> character = Cast<ASwitchBall_UE5Character>(OtherActor);
	if (character) {
		GetWorld()->GetTimerManager().ClearTimer(timeHandle);
	}
}

void ATimerMoveTriggerBox::MoveTarget() {
	if (targetMovementComp) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("movement Set"));
		targetMovementComp->SetDestination(xDistance, yDistance, zDistance, timeToReachDest, secToWait);
	}
}