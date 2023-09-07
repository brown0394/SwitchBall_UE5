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
		// Set the sphere's collision radius.
		collisionComponent->InitSphereRadius(0.3f);
		// Set the root component to be the collision component.
		RootComponent = collisionComponent;
	}
	if (!projectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		projectileMovementComponent->SetUpdatedComponent(collisionComponent);
		projectileMovementComponent->InitialSpeed = 3000.0f;
		projectileMovementComponent->MaxSpeed = 3000.0f;
		projectileMovementComponent->bRotationFollowsVelocity = true;
		projectileMovementComponent->bShouldBounce = true;
		projectileMovementComponent->Bounciness = 0.3f;
		projectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		staticMesh->SetStaticMesh(MeshAsset.Object);
	}

	RootComponent = staticMesh;
	staticMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));

	DisableBall();
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
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	staticMesh->SetSimulatePhysics(true);
}

void ASwitchBallBase::DisableBall() {
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
	staticMesh->SetSimulatePhysics(false);
}

void ASwitchBallBase::AfterSwitch() {
	SetActorLocation(defaultLocation);
	DisableBall();
}

void ASwitchBallBase::FireInDirection(const FVector& ShootDirection) {
	projectileMovementComponent->Velocity = ShootDirection * projectileMovementComponent->InitialSpeed;
}