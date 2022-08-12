// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapController.h"

void UMiniMapController::SetTimerManager(FTimerManager* NewTimerManager)
{
	TimerManager = NewTimerManager;
}

void UMiniMapController::SetupController(
	UImage* NewMiniMapImage, 
	USceneCaptureComponent2D* NewMiniMapCapture,
	UMaterialInterface* NewMiniMapMaterial)
{
	MiniMapImage = NewMiniMapImage;
	MiniMapCapture = NewMiniMapCapture;
	MiniMapMaterial = NewMiniMapMaterial;
}

void UMiniMapController::RenderLiveEvent(
	UMaterialInterface* LiveEventMaterial, 
	AMiniMapCamera* LiveEventCamera,
	float TimeInSeconds)
{
	FTimerDelegate TimerFinishedDelegate;
	TimerFinishedDelegate.BindUFunction(this, "RenderLiveEvent_Elapsed", LiveEventCamera);
	TimerManager->SetTimer(TimerHandle, TimerFinishedDelegate, TimeInSeconds, false);;

	LiveEventCamera->ToggleCamera(true);
	MiniMapCapture->bCaptureEveryFrame = false;
	MiniMapCapture->bCaptureOnMovement = false;

	MiniMapImage->SetBrushFromMaterial(LiveEventMaterial);
}

void UMiniMapController::RenderLiveEvent_Elapsed(AMiniMapCamera* LiveEventCamera)
{
	MiniMapCapture->bCaptureEveryFrame = true;
	MiniMapCapture->bCaptureOnMovement = true;
	MiniMapImage->SetBrushFromMaterial(MiniMapMaterial);
	LiveEventCamera->ToggleCamera(false);
}