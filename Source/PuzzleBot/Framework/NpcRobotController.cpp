// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcRobotController.h"

void ANpcRobotController::BeginPlay()
 {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANpcRobotController::SearchAndDestroy, 3.0f, true);

	Robot = GetPawn<ARobotCharacter>();
	if (Robot && Robot->NavMeshes.Num() <= 0)
	{
		FVector Location = GetPawn()->GetActorLocation();
		for (TActorIterator<AVolume> It(GetWorld()); It; ++It)
		{
			AVolume* CurrentVolume = *It;

			FBox3d Box = CurrentVolume->GetBounds().GetBox();
			if (Box.IsInside(Robot->GetActorLocation()))
			{
				Robot->NavMeshes.Add(CurrentVolume);
				break;
			}
		}
	}
}

void ANpcRobotController::SearchAndDestroy()
{
	if (TargetOrb || Robot->NavMeshes.Num() <= 0)
		return;

	TargetOrb = NULL;

	for (TActorIterator<AOrb> It(GetWorld()); It; ++It)
	{
		AOrb* CurrentOrb = *It;
		if (!CurrentOrb)
			continue;

		if (IsInsideNavMesh((*It)->GetActorLocation()))
		{
			TargetOrb = CurrentOrb;
			break;
		}
	}

	if (!TargetOrb)
		return;

	MoveToActor(TargetOrb);
}

bool ANpcRobotController::IsInsideNavMesh(FVector ActorLocation)
{
	for (AVolume* CurrentVolume : Robot->NavMeshes)
	{
		FBox3d NavMeshBox = CurrentVolume->GetBounds().GetBox();
		if (NavMeshBox.IsInside(ActorLocation))
			return true;
	}

	return false;
}

void ANpcRobotController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (TargetOrb)
	{
		TargetOrb = NULL;
	}

	SearchAndDestroy();
}