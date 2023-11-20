// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PusherAIController.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API APusherAIController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY()
		TObjectPtr<UBehaviorTreeComponent> BehaviorComp;

	UPROPERTY()
		TObjectPtr<UBlackboardComponent> BlackboardComp;

public:
	APusherAIController();
	virtual void OnPossess(APawn* InPawn) override;
	FBlackboard::FKey TargetKeyID;
};
