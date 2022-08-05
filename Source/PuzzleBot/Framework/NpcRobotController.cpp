// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcRobotController.h"

void ANpcRobotController::BeginPlay()
 {
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANpcRobotController::SearchAndDestroy, 3.0f, true);

	FVector Location = GetPawn()->GetActorLocation();
	for (TActorIterator<AVolume> It(GetWorld()); It; ++It)
	{
		AVolume* CurrentVolume = *It;

		FBox3d Box = CurrentVolume->GetBounds().GetBox();
		if (Box.IsInside(GetPawn()->GetActorLocation()))
		{
			NavMesh = CurrentVolume;
			break;
		}
	}
}

void ANpcRobotController::SearchAndDestroy()
{
	if (TargetOrb || !NavMesh)
		return;

	TargetOrb = NULL;

	FBox3d NavMeshBox = NavMesh->GetBounds().GetBox();
	for (TActorIterator<AOrb> It(GetWorld()); It; ++It)
	{
		if (NavMeshBox.IsInside((*It)->GetActorLocation()))
		{
			TargetOrb = *It;
			break;
		}
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