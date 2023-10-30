// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwitchBallWidget.generated.h"

/**
 * 
 */

enum ballType {
	SWITCHBALL = 0,
	STICKYBALL,
	EYEBALL
};
UCLASS()
class SWITCHBALL_UE5_API USwitchBallWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetChargeBar(float &currentCharge, float chargeLimit);

	void SetChargeBarVisibility(bool on);
	void SetSwitchBallTextVisibility(bool on, ballType type);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* ChargeBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* SwitchBallText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* StickyBallText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* EyeBallText;
};

