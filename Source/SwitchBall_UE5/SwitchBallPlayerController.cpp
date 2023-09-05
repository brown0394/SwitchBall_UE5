// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallPlayerController.h"
#include "SwitchBallWidget.h"
#include "Blueprint/UserWidget.h"


ASwitchBallPlayerController::ASwitchBallPlayerController() {
	SBWidgetClass = nullptr;
	sbWidget = nullptr;
}

void ASwitchBallPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (SBWidgetClass) {
		sbWidget = CreateWidget<USwitchBallWidget>(this, SBWidgetClass);
		sbWidget->SetVisibility(ESlateVisibility::Hidden);
		sbWidget->AddToViewport();
	}
}

void ASwitchBallPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (sbWidget) {
		sbWidget->RemoveFromParent();
		sbWidget = nullptr;
	}
	if (SBWidgetClass) {
		SBWidgetClass = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void ASwitchBallPlayerController::setWidgetVisiblilty(bool on) {
	if (on) {
		sbWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		sbWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void ASwitchBallPlayerController::updateWidget(float &progressVal, float progressMax) {
	sbWidget->SetChargeBar(progressVal, progressMax);
}