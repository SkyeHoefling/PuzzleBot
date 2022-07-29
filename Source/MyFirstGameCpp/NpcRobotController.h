// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "RobotCharacter.h"
#include "OrbActor.h"
#include "NpcRobotController.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMECPP_API ANpcRobotController : public AAIController
{
	GENERATED_BODY()
		
private:
	void SearchAndDestroy();

	FVector Destination;
	FTimerHandle TimerHandle;
	AOrbActor* TargetOrb;
protected:
	virtual void BeginPlay() override;
public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
