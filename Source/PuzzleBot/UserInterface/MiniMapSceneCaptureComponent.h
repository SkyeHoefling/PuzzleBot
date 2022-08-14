// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MiniMapSceneCaptureComponent.generated.h"

/**
 * 
 */
UCLASS(hidecategories = (Collision, Object, Physics, SceneComponent), ClassGroup = Rendering, editinlinenew, meta = (BlueprintSpawnableComponent))
class PUZZLEBOT_API UMiniMapSceneCaptureComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()

public:
	UMiniMapSceneCaptureComponent();
	
	UFUNCTION(BlueprintCallable)
	void ToggleCamera(bool isCameraCapturingFrames);
};
