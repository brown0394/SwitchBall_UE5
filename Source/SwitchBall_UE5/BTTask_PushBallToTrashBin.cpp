// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PushBallToTrashBin.h"
#include "PusherAIController.h"


EBTNodeResult::Type UBTTask_PushBallToTrashBin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	APusherAIController* pusherController = Cast<APusherAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* blackBoard = OwnerComp.GetBlackboardComponent();
	if (pusherController) {
		pusherController->MoveToActor(Cast<AActor>(blackBoard->GetValueAsObject("TrashBin")));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
