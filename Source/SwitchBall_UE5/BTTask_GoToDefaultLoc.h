// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GoToDefaultLoc.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API UBTTask_GoToDefaultLoc : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
