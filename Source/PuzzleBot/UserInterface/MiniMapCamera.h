// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MiniMapCamera.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API AMiniMapCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	AMiniMapCamera();
	
	UPROPERTY(VisibleAnywhere);
	USceneCaptureComponent2D* SceneCaptureComponent2D;
	
	UFUNCTION(BlueprintCallable)
	void ToggleCamera(bool isCameraCapturingFrames);
};
