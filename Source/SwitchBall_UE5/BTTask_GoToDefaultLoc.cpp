// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToDefaultLoc.h"
#include "PusherAIController.h"


EBTNodeResult::Type UBTTask_GoToDefaultLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	TObjectPtr<APusherAIController> pusherController = Cast<APusherAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	//ASwitchBallBase* ball = Cast<ASwitchBallBase>(blackBoard->GetValue<UBlackboardKeyType_Object>(pusherController->TargetKeyID));
	if (pusherController) {
		pusherController->MoveToLocation(blackBoard->GetValueAsVector("DefaultLocation"));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}