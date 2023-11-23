// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsBallOverlapped.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API UBTDecorator_IsBallOverlapped : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
