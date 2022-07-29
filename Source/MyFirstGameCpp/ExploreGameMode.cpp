// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreGameMode.h"

// Sets default values
AExploreGameMode::AExploreGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
	PlayerControllerClass = ARobotPlayerController::StaticClass();
}