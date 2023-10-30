// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USwitchBallWidget::SetChargeBar(float &currentCharge, float chargeLimit) {
	if (ChargeBar) {
		if (currentCharge < 0.0f) {
			currentCharge = 0.0f;
		}
		else if (currentCharge > chargeLimit) {
			currentCharge = chargeLimit;
		}
		ChargeBar->SetPercent(currentCharge / chargeLimit);
	}
}

void USwitchBallWidget::SetChargeBarVisibility(bool on) {
	if (ChargeBar) {
		if (on) {
			ChargeBar->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			ChargeBar->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void USwitchBallWidget::SetSwitchBallTextVisibility(bool on, ballType type) {
	UTextBlock* textBlock = nullptr;
	switch (type) {
	case SWITCHBALL: {textBlock = SwitchBallText; break; }
	case STICKYBALL: {textBlock = StickyBallText; break; }
	case EYEBALL: {textBlock = EyeBallText; break; }
	}
	if (textBlock) {
		if (on) {
			textBlock->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			textBlock->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}