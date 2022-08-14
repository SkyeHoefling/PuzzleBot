// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapController.h"

void UMiniMapController::SetTimerManager(FTimerManager* NewTimerManager)
{
	TimerManager = NewTimerManager;
}

void UMiniMapController::SetupController(
	UImage* NewMiniMapImage, 
	UMiniMapSceneCaptureComponent* NewMiniMapCamera,
	UMaterialInterface* NewMiniMapMaterial)
{
	MiniMapImage = NewMiniMapImage;
	MiniMapCamera = NewMiniMapCamera;
	MiniMapMaterial = NewMiniMapMaterial;
}

// this method still can drop the framerate by about 10fps
void UMiniMapController::RenderLiveEvent(
	UMaterialInterface* LiveEventMaterial, 
	UMiniMapSceneCaptureComponent* LiveEventCamera,
	float TimeInSeconds)
{
	FTimerDelegate TimerFinishedDelegate;
	TimerFinishedDelegate.BindUFunction(this, "RenderLiveEvent_Elapsed", LiveEventCamera);
	TimerManager->SetTimer(TimerHandle, TimerFinishedDelegate, TimeInSeconds, false);;

	MiniMapCamera->ToggleCamera(false);
	LiveEventCamera->ToggleCamera(true);
	MiniMapImage->SetBrushFromMaterial(LiveEventMaterial);
}

void UMiniMapController::RenderLiveEvent_Elapsed(UMiniMapSceneCaptureComponent* LiveEventCamera)
{
	LiveEventCamera->ToggleCamera(false);
	MiniMapCamera->ToggleCamera(true);
	MiniMapImage->SetBrushFromMaterial(MiniMapMaterial);
}