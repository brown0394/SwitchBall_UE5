// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchTriggerBox.h"
#include "Engine/PointLight.h"
#include "SwitchBallBase.h"

ALaunchTriggerBox::ALaunchTriggerBox() {
	PointLight = nullptr;
	ballOverlapped = nullptr;
	period = 0.0f;
}

void ALaunchTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	Idle();
}

void ALaunchTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	TObjectPtr<ASwitchBallBase> ball = Cast<ASwitchBallBase>(OtherActor);
	if (ball) {
		ballOverlapped = ball;
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("overlapped"));
	}
}

void ALaunchTriggerBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	TObjectPtr<ASwitchBallBase> ball = Cast<ASwitchBallBase>(OtherActor);
	if (ball) {
		ballOverlapped = nullptr;
	}
}

void ALaunchTriggerBox::Launch() {
	if (PointLight) {
		PointLight->SetLightColor(FLinearColor::Green);
	}
	if (period > 0.0f) {
		GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &ALaunchTriggerBox::Idle, period, false);
	}
	if (ballOverlapped) {
		ballOverlapped->FireInDirection(GetActorForwardVector(), ForceToLaunch);
	}
}

void ALaunchTriggerBox::Idle() {
	if (PointLight) {
		PointLight->SetLightColor(FLinearColor::Red);
	}
	if (period > 0.0f) {
		GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &ALaunchTriggerBox::Launch, period, false);
	}
}