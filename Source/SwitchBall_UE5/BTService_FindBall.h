// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BTService_FindBall.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API UBTService_FindBall : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_FindBall();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
