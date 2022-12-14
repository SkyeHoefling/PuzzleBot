// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Character/RobotCharacter.h"
#include "RobotPlayerController.h"
#include "ExploreGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API AExploreGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AExploreGameMode();
};
