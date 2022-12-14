// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateOncePressurePlate.h"

void AActivateOncePressurePlate::OnEnterPlate(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IsPlateActivated)
		return;

	PawnsOnPlate++;
	IsPlateActivated = true;
	if (PawnsOnPlate == 1)
	{
		OnPlateStatusChanged.Broadcast(true, this);
		PlateAnimation.Play();
	}
}

void AActivateOncePressurePlate::OnExitPlate(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	PawnsOnPlate--;
}

bool AActivateOncePressurePlate::IsActivated()
{
	return IsPlateActivated;
}
