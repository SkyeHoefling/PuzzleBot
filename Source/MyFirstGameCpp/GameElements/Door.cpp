// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	AnchorDoorLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor Door Left"));
	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left Mesh"));
	AnchorDoorRight = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor Door Right"));
	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right Mesh"));

	SetRootComponent(WallMesh);
	
	AnchorDoorLeft->SetupAttachment(WallMesh);
	DoorLeft->SetupAttachment(AnchorDoorLeft);

	AnchorDoorRight->SetupAttachment(WallMesh);
	DoorRight->SetupAttachment(AnchorDoorRight);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WallVisualAsset(TEXT("StaticMesh'/Game/Props/SM_Modular_WallDoor.SM_Modular_WallDoor'"));
	if (WallVisualAsset.Succeeded())
	{
		WallMesh->SetStaticMesh(WallVisualAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorVisualAsset(TEXT("StaticMesh'/Game/Props/SM_Door.SM_Door'"));
	if (DoorVisualAsset.Succeeded())
	{
		DoorLeft->SetStaticMesh(DoorVisualAsset.Object);
		DoorRight->SetStaticMesh(DoorVisualAsset.Object);
	}

	AnchorDoorLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	AnchorDoorLeft->SetRelativeLocation(FVector(0.0f, 330.0f, 0.0f));

	AnchorDoorRight->SetRelativeLocation(FVector(0.0f, 170.0f, 0.0f));

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

