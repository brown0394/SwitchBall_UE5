// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveToBall.h"
#include "PusherAIController.h"
#include "SwitchBallBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


EBTNodeResult::Type UMyBTTask_MoveToBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	APusherAIController* pusherController = Cast<APusherAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	ASwitchBallBase* ball = Cast<ASwitchBallBase>(blackBoard->GetValue<UBlackboardKeyType_Object>(pusherController->TargetKeyID));

	if (ball) {
		pusherController->MoveToActor(ball, 50.0f);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}