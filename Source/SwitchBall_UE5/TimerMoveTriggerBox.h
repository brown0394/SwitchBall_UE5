// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TimerMoveTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API ATimerMoveTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	ATimerMoveTriggerBox();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Target")
		TObjectPtr<AActor> target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		float xDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		float yDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		float zDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		float timeToReachDest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		float secToWait;


protected:
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
	void MoveTarget();
	TObjectPtr<class ULiftMovementComponent> targetMovementComp;
	UPROPERTY()
		FTimerHandle timeHandle;
};
