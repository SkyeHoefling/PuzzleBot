// Fill out your copyright notice in the Description page of Project Settings.


#include "Crate.h"

// Sets default values
ACrate::ACrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrateMesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrateVisualAsset(TEXT("StaticMesh'/Game/Props/SM_Crate.SM_Crate'"));
	if (CrateVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CrateVisualAsset.Object);
	}

	VisualMesh->SetSimulatePhysics(true);
	VisualMesh->SetMassOverrideInKg(NAME_None, 50.0f);
}

// Called when the game starts or when spawned
void ACrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

