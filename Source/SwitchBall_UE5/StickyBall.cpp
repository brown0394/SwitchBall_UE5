// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AStickyBall::BeginPlay()
{
	Super::BeginPlay();
	//staticMesh->OnComponentHit.AddDynamic(this, &AStickyBall::OnHit);
}

/*void AStickyBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	staticMesh->SetSimulatePhysics(false);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("hit"));
}*/

void AStickyBall::NotifyHit(
    UPrimitiveComponent* MyComp,
    AActor* Other,
    UPrimitiveComponent* OtherComp,
    bool bSelfMoved,
    FVector HitLocation,
    FVector HitNormal,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
    projectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);
    projectileMovementComponent->SetUpdatedComponent(collisionComponent);
    AttachToActor(Other, FAttachmentTransformRules::KeepWorldTransform);
}

void AStickyBall::DisableBall() {
   DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AStickyBall::EnableBall() {
   DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}