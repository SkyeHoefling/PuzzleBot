// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "GameFramework/Volume.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/RobotCharacter.h"
#include "../GameElements/Orb.h"
#include "NpcRobotController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API ANpcRobotController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
protected:
	virtual void BeginPlay() override;
private:
	void SearchAndDestroy();
	bool IsInsideNavMesh(FVector ActorLocation);

	UPROPERTY(Transient);
	ARobotCharacter* Robot;

	FVector Destination;
	FTimerHandle TimerHandle;
	AOrb* TargetOrb;
};
