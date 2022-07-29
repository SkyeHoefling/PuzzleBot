// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = GetCapsuleComponent();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RobotVisualAsset(TEXT("/Game/Character/SKM_Antbot.SKM_Antbot"));
	if (RobotVisualAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(RobotVisualAsset.Object);
	}

	Capsule->SetCapsuleHalfHeight(70.0f);
	Capsule->SetCapsuleRadius(25.0f);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}