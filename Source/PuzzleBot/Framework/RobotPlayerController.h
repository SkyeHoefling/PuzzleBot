// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Character/RobotCharacterWithCamera.h"
#include "../GameElements/Orb.h"
#include "../Maps/GameLevel.h"
#include "RobotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	void MoveY(float AxisValue);
	void MoveX(float AxisValue);
	void SpringArmY(float AxisValue);
	void SpringArmX(float AxisValue);
	void SpawnOrb();
	void ToggleCamera();
	void ToggleMenuGamepad();
	void ToggleMenuKeyboard();

	ARobotCharacterWithCamera* Robot;
protected:
	virtual void BeginPlay() override;
};
