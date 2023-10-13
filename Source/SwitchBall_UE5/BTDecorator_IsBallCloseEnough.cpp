// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsBallCloseEnough.h"
#include "PusherCharacter.h"
#include "PusherAIController.h"

bool UBTDecorator_IsBallCloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const {
	APusherCharacter* character = Cast<APusherCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (character) {
		return character->isBallCloseEnough();
	}
	return false;
}