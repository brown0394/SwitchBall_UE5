// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASwitchBallBase::ASwitchBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!collisionComponent)
	{
		// Use a sphere as a simple collision representation.
		collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		collisionComponent->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
		// Set the sphere's collision radius.
		collisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = collisionComponent;
	}
	if (!projectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		projectileMovementComponent->InitialSpeed = 150.0f;
		projectileMovementComponent->MaxSpeed = 1500.0f;
		projectileMovementComponent->bRotationFollowsVelocity = true;
		projectileMovementComponent->bShouldBounce = true;
		projectileMovementComponent->Bounciness = 0.3f;
		projectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
		projectileMovementComponent->SetUpdatedComponent(collisionComponent);
	}
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		staticMesh->SetStaticMesh(MeshAsset.Object);
		staticMesh->SetupAttachment(collisionComponent);
		staticMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
	}

	//DisableBall();
}

// Called when the game starts or when spawned
void ASwitchBallBase::BeginPlay()
{
	Super::BeginPlay();
	defaultLocation = GetActorLocation();
}

// Called every frame
void ASwitchBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitchBallBase::EnableBall() {

}

void ASwitchBallBase::DisableBall() {
	//staticMesh->SetSimulatePhysics(false);
	//collisionComponent->SetSimulatePhysics(false);
}

void ASwitchBallBase::AfterSwitch() {
	SetActorLocation(defaultLocation);
	DisableBall();
}

void ASwitchBallBase::FireInDirection(const FVector& ShootDirection, float impulseCharge) {
	EnableBall();
	projectileMovementComponent->Velocity = ShootDirection * projectileMovementComponent->InitialSpeed * impulseCharge; 
	projectileMovementComponent->SetUpdatedComponent(collisionComponent);
}