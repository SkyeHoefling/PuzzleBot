// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbActor.h"

// Sets default values
AOrbActor::AOrbActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> OrbVisualAsset(TEXT("/Game/Props/SM_Pickup_Orb.SM_Pickup_Orb"));
	if (OrbVisualAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(OrbVisualAsset.Object);
	}

	// prevent physical collisions with pawns and camera
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AOrbActor::OnOrbCollected);
}

// Called when the game starts or when spawned
void AOrbActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOrbActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOrbActor::OnOrbCollected(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn || Pawn->IsPlayerControlled())
		return;

	Destroy();
}
