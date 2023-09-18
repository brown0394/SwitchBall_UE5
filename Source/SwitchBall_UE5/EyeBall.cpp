// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeBall.h"
#include "Camera/CameraComponent.h"

AEyeBall::AEyeBall() {
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}