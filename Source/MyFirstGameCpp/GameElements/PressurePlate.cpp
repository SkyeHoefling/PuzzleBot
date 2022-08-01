// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Frame"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Platform"));

	FrameMesh->SetupAttachment(RootComponent);
	PlatformMesh->SetupAttachment(FrameMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FrameVisualAsset(TEXT("StaticMesh'/Game/Props/SM_PressurePlate_Frame.SM_PressurePlate_Frame'"));
	if (FrameVisualAsset.Succeeded())
	{
		FrameMesh->SetStaticMesh(FrameVisualAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformVisualAsset(TEXT("StaticMesh'/Game/Props/SM_PressurePlate_Platform.SM_PressurePlate_Platform'"));
	if (PlatformVisualAsset.Succeeded())
	{
		PlatformMesh->SetStaticMesh(PlatformVisualAsset.Object);
	}
}

void APressurePlate::OnConstruction(const FTransform& Transform)
{
	UMaterialInstanceDynamic* FrameMaterial = FrameMesh->CreateDynamicMaterialInstance(0);
	FrameMaterial->SetVectorParameterValue(FName("PlasticColor"), FrameColor);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

