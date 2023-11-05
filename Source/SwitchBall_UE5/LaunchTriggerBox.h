// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LaunchTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API ALaunchTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	ALaunchTriggerBox();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher")
		class APointLight* PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher")
		float period;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher")
		float ForceToLaunch;

	UPROPERTY()
		FTimerHandle timeHandle;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
	virtual void BeginPlay() override;

	void Launch();
	void Idle();

	class ASwitchBallBase* ballOverlapped;
};
