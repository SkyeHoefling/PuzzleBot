// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapEventCamera.h"

AMiniMapEventCamera::AMiniMapEventCamera()
{
    SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent2D");
    SceneCaptureComponent2D->SetupAttachment(RootComponent);

    SceneCaptureComponent2D->bCaptureEveryFrame = false;
}

void AMiniMapEventCamera::ToggleCamera(bool IsCameraCapturingFrames)
{
    SceneCaptureComponent2D->bCaptureEveryFrame = IsCameraCapturingFrames;
}