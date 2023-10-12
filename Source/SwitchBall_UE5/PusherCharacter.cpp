// Fill out your copyright notice in the Description page of Project Settings.


#include "PusherCharacter.h"
#include "Components/SphereComponent.h"
#include "SwitchBallBase.h"

// Sets default values
APusherCharacter::APusherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	OverlapSphere->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	OverlapSphere->SetupAttachment(RootComponent);
	ballOverlapped = false;
}

// Called when the game starts or when spawned
void APusherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APusherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APusherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APusherCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ballOverlapped = Cast<ASwitchBallBase>(OtherActor);
	if (ballOverlapped) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("overlapped"));
	}
}

void APusherCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	ASwitchBallBase* ball = Cast<ASwitchBallBase>(OtherActor);
	if (ball) {
		ballOverlapped = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("end overlap"));
	}
}

ASwitchBallBase* APusherCharacter::getBallOverlapped() {
	return ballOverlapped;
}