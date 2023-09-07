// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwitchBallBase.h"
#include "StickyBall.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API AStickyBall : public ASwitchBallBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    void NotifyHit(
        UPrimitiveComponent* MyComp,
        AActor* Other,
        UPrimitiveComponent* OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult& Hit
    );
};
