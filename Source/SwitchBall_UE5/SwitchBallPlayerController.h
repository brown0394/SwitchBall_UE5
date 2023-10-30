// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SwitchBallWidget.h"
#include "SwitchBallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SWITCHBALL_UE5_API ASwitchBallPlayerController : public APlayerController
{
	GENERATED_BODY()
public: 
	ASwitchBallPlayerController();
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<USwitchBallWidget> SBWidgetClass;

	void setProgressBarVisiblilty(bool on);
	void setBallTextVisiblilty(bool on, ballType type);
	void updateWidget(float &progressVal, float progressMax);

private:
	UPROPERTY()
		USwitchBallWidget* sbWidget;

protected:
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
