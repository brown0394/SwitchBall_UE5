// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallPlayerController.h"
#include "Blueprint/UserWidget.h"


ASwitchBallPlayerController::ASwitchBallPlayerController() {
	SBWidgetClass = nullptr;
	sbWidget = nullptr;
}

void ASwitchBallPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (SBWidgetClass) {
		sbWidget = CreateWidget<USwitchBallWidget>(this, SBWidgetClass);
		sbWidget->SetChargeBarVisibility(false);
		sbWidget->SetSwitchBallTextVisibility(false, ballType::SWITCHBALL);
		sbWidget->SetSwitchBallTextVisibility(false, ballType::STICKYBALL);
		sbWidget->SetSwitchBallTextVisibility(false, ballType::EYEBALL);
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

void ASwitchBallPlayerController::setProgressBarVisiblilty(bool on) {
	sbWidget->SetChargeBarVisibility(on);
}

void ASwitchBallPlayerController::updateWidget(float &progressVal, float progressMax) {
	sbWidget->SetChargeBar(progressVal, progressMax);
}

void ASwitchBallPlayerController::setBallTextVisiblilty(bool on, ballType type) {
	sbWidget->SetSwitchBallTextVisibility(on, type);
}