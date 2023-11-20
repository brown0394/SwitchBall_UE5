// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAwayFromPawn.h"
#include "PusherAIController.h"
#include "PusherCharacter.h"
#include "SwitchBall_UE5Character.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_MoveAwayFromPawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	TObjectPtr<APusherAIController> pusherController = Cast<APusherAIController>(OwnerComp.GetAIOwner());
	TObjectPtr<APusherCharacter> character = Cast<APusherCharacter>(pusherController->GetCharacter());
	if (character) {
		ASwitchBall_UE5Character* player = character->getPlayerOverlapped();
		if (player) {
			FVector curLoc = character->GetActorLocation();
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(curLoc, player->GetActorLocation());
			FVector newLoc = (UKismetMathLibrary::GetForwardVector(rot) * -100);
			newLoc.Z = 0.0f;
			newLoc += curLoc;
			pusherController->MoveToLocation(newLoc);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}