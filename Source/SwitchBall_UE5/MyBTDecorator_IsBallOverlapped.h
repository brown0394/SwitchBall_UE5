// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MyBTDecorator_IsBallOverlapped.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API UMyBTDecorator_IsBallOverlapped : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
