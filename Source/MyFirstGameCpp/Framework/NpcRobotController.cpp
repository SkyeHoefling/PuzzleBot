// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcRobotController.h"

void ANpcRobotController::BeginPlay()
 {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANpcRobotController::SearchAndDestroy, 3.0f, true);
	Destination = FVector(-5320.0f, 5420.0f, 170.0f);
	MoveToLocation(Destination);
}

void ANpcRobotController::SearchAndDestroy()
{
	if (TargetOrb)
		return;

	UWorld* World = GetWorld();
	TargetOrb = NULL;
	
	for (TActorIterator<AOrb> It(World); It; ++It)
	{
		TargetOrb = *It;
		break;
	}

	if (!TargetOrb)
		return;

	MoveToActor(TargetOrb);
}

void ANpcRobotController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (TargetOrb)
	{
		TargetOrb = NULL;
	}

	SearchAndDestroy();
}