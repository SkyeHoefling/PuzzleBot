// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreGameMode.h"

// Sets default values
AExploreGameMode::AExploreGameMode()
{
	DefaultPawnClass = ARobotCharacterWithCamera::StaticClass();
	PlayerControllerClass = ARobotPlayerController::StaticClass();
}