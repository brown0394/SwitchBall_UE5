// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToBall.h"
#include "PusherCharacter.h"
#include "PusherAIController.h"
#include "SwitchBallBase.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


EBTNodeResult::Type UBTTask_MoveToBall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	APusherAIController* pusherController = Cast<APusherAIController>(OwnerComp.GetAIOwner());
	APusherCharacter* pusherCharacter = Cast<APusherCharacter>(pusherController->GetCharacter());
	//UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	//ASwitchBallBase* ball = Cast<ASwitchBallBase>(blackBoard->GetValue<UBlackboardKeyType_Object>(pusherController->TargetKeyID));
	ASwitchBallBase* ball = pusherCharacter->getBallOverlapped();
	if (ball) {
		pusherController->MoveToActor(ball);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
