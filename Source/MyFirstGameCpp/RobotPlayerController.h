// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RobotCharacterWithCamera.h"
#include "OrbActor.h"
#include "RobotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMECPP_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	void MoveY(float AxisValue);
	void MoveX(float AxisValue);
	void SpringArmY(float AxisValue);
	void SpringArmX(float AxisValue);
	void SpawnOrb();

	ARobotCharacterWithCamera* Robot;
protected:
	virtual void BeginPlay() override;
};
