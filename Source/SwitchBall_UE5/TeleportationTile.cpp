// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationTile.h"
#include "Kismet/GameplayStatics.h"
#include "SwitchBall_UE5Character.h"
#include "PusherCharacter.h"

// Sets default values
ATeleportationTile::ATeleportationTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("TeleTileStaticMesh");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("TeleTileStaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr) {
		staticMesh->SetStaticMesh(MeshAsset.Object);
		staticMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
		RootComponent = staticMesh;
		/*static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Script/Engine.Material'/Game/ThirdPerson/Blueprints/TeleportTile_Material.TeleportTile_Material'"));
		if (Material.Succeeded())
		{
			materialInstance = UMaterialInstanceDynamic::Create(Material.Object, staticMesh);
		}
		staticMesh->SetMaterial(0, materialInstance);*/
		staticMesh->SetMobility(EComponentMobility::Static);
		staticMesh->SetNotifyRigidBodyCollision(true);
		staticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	}
	auto SoundAsset = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/ThirdPerson/Audio/MS_TeleportMetaSoundSource.MS_TeleportMetaSoundSource'"));
	if (SoundAsset.Succeeded()) {
		TeleportationSound = SoundAsset.Object;
	}
}

// Called when the game starts or when spawned
void ATeleportationTile::BeginPlay()
{
	Super::BeginPlay();
	playerStartLocation = (Cast<ASwitchBall_UE5Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))->GetActorLocation();
}

// Called every frame
void ATeleportationTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportationTile::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other,
	UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	APusherCharacter* pusher = Cast<APusherCharacter>(Other);
	if (pusher == nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, TeleportationSound, GetActorLocation());
		Other->SetActorLocation(playerStartLocation);
	}
}