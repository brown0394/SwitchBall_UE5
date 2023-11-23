// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsBallOverlapped.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PusherAIController.h"
#include "PusherCharacter.h"

bool UBTDecorator_IsBallOverlapped::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const {
	APusherCharacter* character = Cast<APusherCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (character) {
		if (character->getBallOverlapped() != nullptr) {
			return true;
		}
	}
	return false;
}
