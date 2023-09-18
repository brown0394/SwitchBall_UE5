// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwitchBallBase.h"
#include "EyeBall.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API AEyeBall : public ASwitchBallBase
{
	GENERATED_BODY()
	

public:
	AEyeBall();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
};
