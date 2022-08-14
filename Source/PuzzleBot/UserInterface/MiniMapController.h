// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Components/Image.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MiniMapSceneCaptureComponent.h"
#include "MiniMapController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEBOT_API UMiniMapController : public UObject
{
	GENERATED_BODY()
	
public:
	typedef void (UMiniMapController::*ToggleCamera)(bool);

	UFUNCTION(BlueprintCallable)
	void SetupController(UImage* NewMiniMapImage, UMiniMapSceneCaptureComponent* NewMiniMapCamera, UMaterialInterface* NewMiniMapMaterial);

	UFUNCTION(BlueprintCallable)
	void RenderLiveEvent(UMaterialInterface* LiveEventMaterial, UMiniMapSceneCaptureComponent* LiveEventCamera, float TimeInSeconds = 1.5f);

	void SetTimerManager(FTimerManager* NewTimerManager);
protected:
	UImage* MiniMapImage;
	UMiniMapSceneCaptureComponent* MiniMapCamera;
	UMaterialInterface* MiniMapMaterial;
	FTimerManager* TimerManager;

	UFUNCTION()
	void RenderLiveEvent_Elapsed(UMiniMapSceneCaptureComponent* LiveEventCamera);
private:
	FTimerHandle TimerHandle;
};
