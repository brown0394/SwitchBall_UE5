// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyBall.h"
#include "Components/SphereComponent.h"
#include "TeleportationTile.h"

void AStickyBall::BeginPlay()
{
	Super::BeginPlay();
	//staticMesh->OnComponentHit.AddDynamic(this, &AStickyBall::OnHit);
    isAttached = false;
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
    if (!isAttached) {
        if (Cast<ATeleportationTile>(Other) == nullptr) {
            collisionComponent->SetSimulatePhysics(false);
            collisionComponent->SetNotifyRigidBodyCollision(false);
            AttachToActor(Other, FAttachmentTransformRules::KeepWorldTransform);
            isAttached = true;
        }
    }
}

void AStickyBall::DisableBall() {
    Super::DisableBall();
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    isAttached = true;
}

void AStickyBall::EnableBall() {
    Super::EnableBall();
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    isAttached = false;
}