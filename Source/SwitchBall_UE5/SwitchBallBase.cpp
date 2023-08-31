// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchBallBase.h"

// Sets default values
ASwitchBallBase::ASwitchBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshAsset.Object != nullptr) {
		staticMesh->SetStaticMesh(MeshAsset.Object);
	}

	RootComponent = staticMesh;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ASwitchBallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitchBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitchBallBase::EnableBall() {
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
	staticMesh->SetSimulatePhysics(true);
}
