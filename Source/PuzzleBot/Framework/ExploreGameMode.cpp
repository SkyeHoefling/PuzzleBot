// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreGameMode.h"

// Sets default values
AExploreGameMode::AExploreGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/Character/BP_PlayerCharacter"));
	if (PlayerPawn.Succeeded())
	{
		DefaultPawnClass = PlayerPawn.Class;
	}

	PlayerControllerClass = ARobotPlayerController::StaticClass();
}