// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPlayerController.h"

void ARobotPlayerController::BeginPlay()
{
	Robot = Cast<ARobotCharacterWithCamera>(GetCharacter());
}

void ARobotPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Movement
	InputComponent->BindAxis("ForwardBack", this, &ARobotPlayerController::MoveY);
	InputComponent->BindAxis("LeftRight", this, &ARobotPlayerController::MoveX);
	InputComponent->BindAxis("Camera_Y", this, &ARobotPlayerController::SpringArmY);
	InputComponent->BindAxis("Camera_X", this, &ARobotPlayerController::SpringArmX);

	// Interactions
	InputComponent->BindAction("SpawnOrb", IE_Pressed, this, &ARobotPlayerController::SpawnOrb);
	InputComponent->BindAction("ToggleCamera", IE_Pressed, this, &ARobotPlayerController::ToggleCamera);
}

void ARobotPlayerController::MoveY(float AxisValue)
{
	if (!Robot)
		return;

	FRotator Rotation = Robot->SpringArm->GetRelativeRotation();
	Rotation.Pitch = 0;
	FVector Direction = Rotation.Vector();
	Robot->AddMovementInput(Direction, AxisValue);
}

void ARobotPlayerController::MoveX(float AxisValue)
{
	if (!Robot)
		return;

	FRotator Rotation = Robot->SpringArm->GetRelativeRotation();
	Rotation.Pitch = 0;
	Rotation.Yaw += 90;
	FVector Direction = Rotation.Vector();
	Robot->AddMovementInput(Direction, AxisValue);
}

void ARobotPlayerController::SpringArmY(float AxisValue)
{
	if (!Robot)
		return;

	Robot->SpringArmY(AxisValue);
}

void ARobotPlayerController::SpringArmX(float AxisValue)
{
	if (!Robot)
		return;

	Robot->SpringArmX(AxisValue);
}

void ARobotPlayerController::SpawnOrb()
{
	FVector Location = Robot->GetActorLocation();
	GetWorld()->SpawnActor(AOrb::StaticClass(), &Location);
}

void ARobotPlayerController::ToggleCamera()
{
	Robot->ToggleCamera();
}