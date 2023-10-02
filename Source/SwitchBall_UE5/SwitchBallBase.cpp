// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallBase.h"
#include "Components/SphereComponent.h"
//#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASwitchBallBase::ASwitchBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SwitchBallSceneComponent"));
	}
	if (!collisionComponent)
	{
		// Use a sphere as a simple collision representation.
		collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SwitchBallSphereComponent"));
		collisionComponent->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
		// Set the sphere's collision radius.
		collisionComponent->InitSphereRadius(15.0f);
		//collisionComponent->SetCollisionProfileName("BlockAll");
		// Set the root component to be the collision component.
		RootComponent = collisionComponent;
	}
	/*if (!projectileMovementComponent)
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
	}*/
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("SwitchBallStaticMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("SwitchBallStaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		staticMesh->SetStaticMesh(MeshAsset.Object);
		staticMesh->SetupAttachment(collisionComponent);
		staticMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
		staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	ImpulseMulValue = 1.0f;
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
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	collisionComponent->SetSimulatePhysics(true);
	SetActorHiddenInGame(false);
}

void ASwitchBallBase::DisableBall() {
	collisionComponent->SetSimulatePhysics(false);
	collisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
}

void ASwitchBallBase::AfterSwitch() {
	DisableBall();
	SetActorLocation(defaultLocation);
}

void ASwitchBallBase::FireInDirection(const FVector& FiringPosition, const FVector& ShootDirection, float impulseCharge) {
	EnableBall();
	//projectileMovementComponent->Velocity = ShootDirection * projectileMovementComponent->InitialSpeed * impulseCharge; 
	//projectileMovementComponent->SetUpdatedComponent(collisionComponent);
	
	SetActorLocation(FiringPosition);
	collisionComponent->AddImpulse(ShootDirection * impulseCharge * ImpulseMulValue);
}