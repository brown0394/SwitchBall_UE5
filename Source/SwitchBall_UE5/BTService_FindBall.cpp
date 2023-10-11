// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindBall.h"
#include "PusherAIController.h"
#include "SwitchBall_UE5Character.h"
#include "SwitchBallBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_FindBall::UBTService_FindBall() {
	bCreateNodeInstance = true;
}

void UBTService_FindBall::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto PusherAIController = Cast<APusherAIController>(OwnerComp.GetAIOwner());

	if (PusherAIController) {
		ASwitchBall_UE5Character* PlayerCharacter = Cast<ASwitchBall_UE5Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (PlayerCharacter) {
			ASwitchBallBase* ball = PlayerCharacter->getBallLaunched();
			if (ball) {
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(PusherAIController->TargetKeyID, ball);
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("found"));
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("not found"));
			}
		}
	}
}