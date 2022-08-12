// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPlayerController.h"

void ARobotPlayerController::BeginPlay()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
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
	
	FInputActionBinding& ToggleMenuGamepadBinding = InputComponent->BindAction("ToggleMenuGamepad", IE_Pressed, this, &ARobotPlayerController::ToggleMenuGamepad);
	ToggleMenuGamepadBinding.bExecuteWhenPaused = true;

	FInputActionBinding& ToggleMenuKeyboard = InputComponent->BindAction("ToggleMenuKeyboard", IE_Pressed, this, &ARobotPlayerController::ToggleMenuKeyboard);
	ToggleMenuKeyboard.bExecuteWhenPaused = true;
}

void ARobotPlayerController::MoveY(float AxisValue)
{
	if (!PlayerCharacter)
		return;

	FRotator Rotation = PlayerCharacter->SpringArm->GetRelativeRotation();
	Rotation.Pitch = 0;
	FVector Direction = Rotation.Vector();
	PlayerCharacter->AddMovementInput(Direction, AxisValue);
}

void ARobotPlayerController::MoveX(float AxisValue)
{
	if (!PlayerCharacter)
		return;

	FRotator Rotation = PlayerCharacter->SpringArm->GetRelativeRotation();
	Rotation.Pitch = 0;
	Rotation.Yaw += 90;
	FVector Direction = Rotation.Vector();
	PlayerCharacter->AddMovementInput(Direction, AxisValue);
}

void ARobotPlayerController::SpringArmY(float AxisValue)
{
	if (!PlayerCharacter)
		return;

	PlayerCharacter->SpringArmY(AxisValue);
}

void ARobotPlayerController::SpringArmX(float AxisValue)
{
	if (!PlayerCharacter)
		return;

	PlayerCharacter->SpringArmX(AxisValue);
}

void ARobotPlayerController::SpawnOrb()
{
	FVector Location = PlayerCharacter->GetActorLocation();
	GetWorld()->SpawnActor(AOrb::StaticClass(), &Location);
}

void ARobotPlayerController::ToggleCamera()
{
	PlayerCharacter->ToggleCamera();
}

void ARobotPlayerController::ToggleMenuGamepad()
{
	if (!PlayerCharacter)
		return;

	PlayerCharacter->TogglePauseMenu(true);
}

void ARobotPlayerController::ToggleMenuKeyboard()
{
	if (!PlayerCharacter)
		return;

	PlayerCharacter->TogglePauseMenu(false);
}