// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAnimationInstance.h"
void UBotAnimationInstance::SetGroundSpeed()
{
	AActor* OwningActor = GetOwningActor();
	FVector Velocity = OwningActor->GetVelocity();
	Velocity.Z = 0.0f;

	GroundSpeed = Velocity.Length();
}