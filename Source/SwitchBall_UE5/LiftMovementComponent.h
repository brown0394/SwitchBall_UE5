// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiftMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWITCHBALL_UE5_API ULiftMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiftMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
		float xDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
		float yDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
		float zDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
		float LerpAlpha;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	FVector defaultLocation;
	FVector targetLocation;
	AActor* owner;
	bool shouldReturn;
};
