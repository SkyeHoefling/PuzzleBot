// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Character/RobotCharacter.h"
#include "../GameElements/Orb.h"
#include "NpcRobotController.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMECPP_API ANpcRobotController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
protected:
	virtual void BeginPlay() override;
private:
	void SearchAndDestroy();

	FVector Destination;
	FTimerHandle TimerHandle;
	AOrb* TargetOrb;
};
