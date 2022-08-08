// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorMoveCameraShake.h"

UDoorMoveCameraShake::UDoorMoveCameraShake()
{
	OscillationDuration = 1.0f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.5f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 3.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 35.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 3.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 35.0f);
}