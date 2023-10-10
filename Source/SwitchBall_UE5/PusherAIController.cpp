// Fill out your copyright notice in the Description page of Project Settings.


#include "PusherAIController.h"
#include "PusherCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

APusherAIController::APusherAIController() {
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void APusherAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	auto character = Cast<APusherCharacter>(InPawn);
	if (character && character->PusherBehaviorTree) {
		TargetKeyID = BlackboardComp->GetKeyID("Target");
		BehaviorComp->StartTree(*character->PusherBehaviorTree);
	}
}