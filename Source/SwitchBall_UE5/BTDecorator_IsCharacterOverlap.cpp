// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsCharacterOverlap.h"
#include "PusherCharacter.h"
#include "PusherAIController.h"

bool UBTDecorator_IsCharacterOverlap::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const {
	APusherCharacter* character = Cast<APusherCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if (character && character->getPlayerOverlapped()) {
		return true;
	}
	return false;
}