// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapSceneCaptureComponent.h"

UMiniMapSceneCaptureComponent::UMiniMapSceneCaptureComponent()
{
    // 2-3 FPS
    bUseRayTracingIfEnabled = false;

    // 1-2 FPS
    bDisableFlipCopyGLES = true;

    // 10-12 FPS
    LODDistanceFactor = 10;

    // 15-20 FPS
    // we can reduce this by 500 or so if we use an arrow icon 
    // instead of viewing the player
    MaxViewDistanceOverride = 1500;

    ToggleCamera(false);
}

void UMiniMapSceneCaptureComponent::ToggleCamera(bool IsCameraCapturingFrames)
{
    bCaptureEveryFrame = IsCameraCapturingFrames;
    bCaptureOnMovement = IsCameraCapturingFrames;
}