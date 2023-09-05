// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwitchBallWidget.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API USwitchBallWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetChargeBar(float &currentCharge, float chargeLimit);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* ChargeBar;
};
