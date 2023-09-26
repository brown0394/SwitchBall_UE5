// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeBall.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SwitchBall_UE5Character.h"
#include "SwitchBallPlayerController.h"



AEyeBall::AEyeBall() {
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("EyeBallFollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	
}

void AEyeBall::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = (Cast<ASwitchBall_UE5Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
	playerController = Cast<ASwitchBallPlayerController> (UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AEyeBall::DisableBall() {
	Super::DisableBall();
	playerController->SetViewTargetWithBlend(PlayerCharacter);
}

void AEyeBall::EnableBall() {
	Super::EnableBall();
	playerController->SetViewTargetWithBlend(this);
}